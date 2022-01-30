
#include <iostream>
#include <stdio.h>
#include "mpi.h"
#include <vector>
#include "chessboard.h"
#define FIRST_THREAD 0
using namespace std;
static uint16_t *vector_to_int16(std::set<chessboard_map> source, uint16_t *res, int l_board);

int main(int argc, char **argv)
{
	int thread, thread_size, processor_name_length;
	int l_board;
	char* processor_name = new char[MPI_MAX_PROCESSOR_NAME * sizeof(char)];
	MPI_Status status;
	// Инициализируем работу MPI
	MPI_Init(&argc, &argv);
	// Получаем имя физического процессора
	MPI_Get_processor_name(processor_name, &processor_name_length);
	// Получаем номер конкретного процесса на котором запущена программа
	MPI_Comm_rank(MPI_COMM_WORLD, &thread);
	// Получаем количество запущенных процессов
	MPI_Comm_size(MPI_COMM_WORLD, &thread_size);
	if(thread == FIRST_THREAD){
		// Выводим информацию о запуске
		printf("----- Programm information -----\n");
		printf(">>> Processor: %s\n", processor_name);
		printf(">>> Num threads: %d\n", thread_size);
		printf(">>> Input length of chessboard: ");
		// Просим пользователья ввести данные на которых будут вычисления
		scanf ("%d", &l_board);
		// Каждому процессу отправляем полученные данные с тегом сообщения 0.
		for (int to_thread = 1; to_thread < thread_size; to_thread++)
			MPI_Send(&l_board, 1, MPI_INT, to_thread, 0, MPI_COMM_WORLD);
	}
	else
		MPI_Recv(&l_board, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    
    //Обозначаем диаппазон рассчетов для конкретного процесса
    int shag = (l_board*l_board)%thread_size == 0 ? (l_board*l_board)/thread_size : (l_board*l_board)/(thread_size-1);
    int diap_start = shag * thread;
    int diap_end = thread == thread_size - 1 ? (l_board*l_board) : diap_start + shag;

    Chessboard chessboard(l_board);
	std::set<chessboard_map> source = chessboard.PrintHardDecision(diap_start, diap_end);
	uint16_t res[source.size()*l_board*l_board];
	//res = vector_to_int16(source, res, l_board);
	if (thread != FIRST_THREAD){
		int i = 0;
		std::set<chessboard_map>::iterator it1, it2;
		for (it1 = source.begin(), it2 = source.end(); it1 != it2; ++it1){
			for (int j = 0; j < l_board; j++)
			{
				for (int k = 0; k <l_board; k++){
					res[i] = (uint16_t)((*it1)[j][k]);
					i++;
				}
			}
		}
	}

	printf ("\n");
	if (thread != FIRST_THREAD)
	{
		MPI_Send (res, (int)source.size()*l_board*l_board,MPI_UNSIGNED_SHORT, 0, 0, MPI_COMM_WORLD);
		//free(res);
	}
	else{
        int count;
		int i = 1;
		uint16_t *j;
		while (i < thread_size){
			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			MPI_Get_count(&status, MPI_UNSIGNED_SHORT, &count);
			j = (uint16_t*)malloc(sizeof(uint16_t)*count);
            MPI_Recv(j, count, MPI_UNSIGNED_SHORT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			i++;
		}
	}
	
	MPI_Finalize();
	return (0);
}