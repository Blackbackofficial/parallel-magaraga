#include "chessboard.h"

int main(int argc, char **argv) {
	int thread, thread_size, processor_name_length;
	int l_board;
	char *processor_name = new char[MPI_MAX_PROCESSOR_NAME * sizeof(char)];
	MPI_Status status;
	MPI_Init(&argc, &argv);  // Инициализируем работу MPI
	MPI_Get_processor_name(processor_name, &processor_name_length);	// Получаем имя физического процессора
	MPI_Comm_rank(MPI_COMM_WORLD, &thread);	// Получаем номер конкретного процесса на котором запущена программа
	MPI_Comm_size(MPI_COMM_WORLD, &thread_size); // Получаем количество запущенных процессов

    clock_t start;
	if (thread == FIRST_THREAD) {
		printf("----- Programm information -----\n"); // Info
		printf(">>> Processor: %s\n", processor_name);
		printf(">>> Num threads: %d\n", thread_size);
		printf(">>> Input length of chessboard: ");
		scanf ("%d", &l_board);
		start = clock(); //начало замера
		// Каждому процессу отправляем полученные данные с тегом сообщения 0.
		for (int to_thread = 1; to_thread < thread_size; to_thread++) {
			MPI_Send(&l_board, 1, MPI_INT, to_thread, 0, MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(&l_board, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	}
    
    //Обозначаем диаппазон рассчетов для конкретного процесса
    int shag = (l_board*l_board%thread_size) == 0 ? (l_board*l_board/thread_size) : (l_board*l_board/thread_size-1);
    int diap_start = shag*thread;
    int diap_end = (thread == thread_size - 1) ? (l_board*l_board) : (diap_start + shag);

    ChessBoard chessBoard(l_board);
	set<chessboard_map> source = chessBoard.PrintHardDecision(diap_start, diap_end);
	uint16_t res[source.size()*l_board*l_board];

	if (thread != FIRST_THREAD) {
		int i = 0;
		set<chessboard_map>::iterator it1, it2;
		for (it1 = source.begin(), it2 = source.end(); it1 != it2; ++it1) {
			for (int j = 0; j < l_board; j++) {
				for (int k = 0; k < l_board; k++) {
					res[i] = (uint16_t)((*it1)[j][k]);
					i++;
				}
			}
		}
	}

	if (thread != FIRST_THREAD) {
		MPI_Send (res, (int)source.size()*l_board*l_board, MPI_UNSIGNED_SHORT, 0, 0, MPI_COMM_WORLD);
	} else {
        int count;
		int i = 1;
		uint16_t *j;
		int w;
		chessboard_map new_map;
		while (i < thread_size) {
			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			MPI_Get_count(&status, MPI_UNSIGNED_SHORT, &count);
			j = (uint16_t*)malloc(sizeof(uint16_t)*count);
            MPI_Recv(j, count, MPI_UNSIGNED_SHORT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			w = 0;
			while (w < count) {
				new_map.resize(l_board);
				for (vector<uint16_t> &x : new_map) { // создали chessboard_size столбцов(x)
					x.resize(l_board, 1); //заполнили true
				}
				for (int q = 0; q < l_board; q++) {
					for (int k = 0; k < l_board; k++) {
						new_map[q][k] = j[w];
						w++;
					}
				}
				source.insert(move(new_map));
			}
			free(j);
			i++;
		}
		printf("%ld\n", source.size());

		clock_t end = clock(); //конец замера
		double seconds = (double)(end - start) / CLOCKS_PER_SEC;
		printf("Time %lf\n", seconds);
	}
	
	MPI_Finalize();
	return 0;
}