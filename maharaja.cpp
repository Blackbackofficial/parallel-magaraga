#include "maharaja.h"


bool Maharaja::full_check() {
        for (auto v : cells)
            if(!v)
                return false;
        return true;
}

int Maharaja::count_ceils(int x, int y) {
    int count = 0;


    for (int i = 0; i < width; i++)
        if (!cells[y*width + i])
            count++;

    for (int i = 0; i < height; i++)
        if (!cells[i*width + x])
            count++;

    if (y > x) {
        for (int i = 0, j = (y-x); i< width, j < height; i++,j++) {
            if (!cells[j*width + i])
                count++;
        }
    } else {
        for (int i = (x-y), j = 0; i< width, j < height; i++,j++) {
            if(!cells[j*width + i])
                count++;
        }
    }

    if (y > (7-x)) {
        for (int i = 7, j = (y + x - 7); i > 0, j < height; i--,j++) {
            if(!cells[j*width + i])
                count++;
        }
    } else {
        for (int i = (x+y), j = 0; i > 0, j < height; i--,j++) {
            if (!cells[j*width + i])
                count++;
        }
    }

    return count-4;
}

position Maharaja::search_min_position() {
    int x_min,y_min;

    int process_num = -1;
    pid_t p;

    int pip[2];

    if (pipe(pip) < 0)
        return {};

    if (fcntl(pip[0], F_SETFL, O_NONBLOCK) < 0)
        return {};

    for (int i = 0; i < processes; i++) {
        p = fork();
        if (p == 0) {
            std::cout << "Создался процесс " << i << std::endl;
            process_num = i;
            break;
        }
    }

    if (process_num != -1) {

        close(pip[0]);

        for (int k = process_num; k < width * height; k += processes) {
            int i = k % width;
            int j = k/width;
            if (cells[k])
                continue;
            int c = count_ceils(i, j);
            std::string tmp_msg = std::to_string(i) + " " + std::to_string(j) + " " + std::to_string(c);
            char message[20];
            strcpy(message, tmp_msg.c_str());
            write(pip[1], message, 20);
            //std::cout << "Процессом " << process_num << " создано сообщение " << message << std::endl;
        }
        //std::cout << "Процесс " << process_num << " завершился" << std::endl;
        close(pip[1]);
        _exit(0);
    }

    close(pip[1]);
    int min_c = width*height;

    int nread;
    char buf[20];

    while (true) {
        int i,j,c;
        nread = (int)read(pip[0], buf, 20);
        if (nread == 0) {
            break;
        } else if (nread != -1) {
            sscanf(buf,"%d %d %d", &i, &j, &c);

            //std::cout << "Процессом " << process_num << " принято сообщение " << i << " " << j << " " << c << std::endl;

            if (c < min_c) {
                x_min = i;
                y_min = j;
                min_c = c;
            }
        }

    }
    close(pip[0]);


    return {x_min,y_min};
}

bool Maharaja::take_position(int x, int y) {
    if (cells[y*width + x]) {
        return false;
    }

    this->positions.emplace_back(x,y);

    for (int i = 0; i < width; i++)
        cells[y*width + i] = true;

    for (int i = 0; i < height; i++)
        cells[i*width + x] = true;

    if (y > x) {
        for (int i = 0, j = (y-x); i< width, j < height; i++,j++) {
            cells[j*width + i] = true;
        }
    } else {
        for (int i = (x-y), j = 0; i< width, j < height; i++,j++) {
            cells[j*width + i] = true;
        }
    }

    if (y > (7-x)) {
        for (int i = 7, j = (y + x - 7); i > 0, j < height; i--,j++) {
            cells[j*width + i] = true;
        }
    } else {
        for (int i = (x+y), j = 0; i > 0, j < height; i--,j++) {
            cells[j*width + i] = true;
        }
    }
    return true;
}

int Maharaja::greedy_filling() {
    int counter = 0;
    while (!full_check()) {
        position p = search_min_position();
        take_position(p.first,p.second);
        counter++;
    }
    return counter;
}

