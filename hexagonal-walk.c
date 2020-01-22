#include <stdio.h>
#include <time.h>
#include <windows.h>

int number_of_possible_paths = 0;

DWORD WINAPI hexagonal_walk(int* test_combination) {

    int coordinates[] = {-1, 1};
    int current_test_combination[13];
    int depth_level = 13; // In realty one more. The first direction is always direction 1.
    int local_possible_paths = 0;
    register int i;
    int end_at;

    for(i = 0; i < 13; i++) {
        current_test_combination[i] = test_combination[i];
    }

    end_at = current_test_combination[0] + 1;

    // 1: x -= 1, y += 1
    // 2: y += 1
    // 3: x += 1
    // 4: x += 1, y -= 1
    // 5: y -= 1
    // 6: x -= 1

    while(current_test_combination[0] != end_at) {

        for(i = 0; i < depth_level; i++) {
            if(current_test_combination[i] == 1) {
                coordinates[0]--;
                coordinates[1]++;
            }
            else if(current_test_combination[i] == 2) {
                coordinates[1]++;
            }
            else if(current_test_combination[i] == 3) {
                coordinates[0]++;
            }
            else if(current_test_combination[i] == 4) {
                coordinates[0]++;
                coordinates[1]--;
            }
            else if(current_test_combination[i] == 5) {
                coordinates[1]--;
            }
            else if(current_test_combination[i] == 6) {
                coordinates[0]--;
            }
        }

        if(coordinates[0] == 0 && coordinates[1] == 0) {
            if(current_test_combination[0] == 1 && current_test_combination[1] == 1 && (current_test_combination[2] == 2 || current_test_combination[2] == 3)) {
                local_possible_paths += 2;
            }
            else if(current_test_combination[0] == 1 && (current_test_combination[1] == 2 || current_test_combination[1] == 3)) {
                local_possible_paths += 2;
            }
            else if(current_test_combination[0] == 2 || current_test_combination[0] == 3) {
                local_possible_paths += 2;
            }
            else {
                local_possible_paths++;
            }
        }

        for(i = depth_level - 1; i >= 0; i--) {
            if(i == 2 && current_test_combination[0] == 1 && current_test_combination[1] == 1 && current_test_combination[2] == 4) {
                current_test_combination[2] = 1;
            }
            else if(i == 1 && current_test_combination[0] == 1 && current_test_combination[1] == 4) {
                current_test_combination[1] = 1;
            }
            else if(current_test_combination[i] == 6) {
                current_test_combination[i] = 1;
            }
            else {
                current_test_combination[i]++;
                break;
            }
        }

        coordinates[0] = -1;
        coordinates[1] = 1;
    }

    number_of_possible_paths += local_possible_paths;
    
    return 0;

}

int main() {

    double time_spent = 0.0;
    clock_t begin = clock();

    int test_combination1[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int test_combination2[] = {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int test_combination3[] = {3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int test_combination4[] = {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    HANDLE thread1 = CreateThread(NULL, 0, hexagonal_walk, &test_combination1, 0, NULL);
    HANDLE thread2 = CreateThread(NULL, 0, hexagonal_walk, &test_combination2, 0, NULL);
    HANDLE thread3 = CreateThread(NULL, 0, hexagonal_walk, &test_combination3, 0, NULL);
    HANDLE thread4 = CreateThread(NULL, 0, hexagonal_walk, &test_combination4, 0, NULL);

    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);
    WaitForSingleObject(thread3, INFINITE);
    WaitForSingleObject(thread4, INFINITE);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Possible paths: %d\n", number_of_possible_paths * 6);
    printf("Time spent: %lf\n", time_spent);

    return(0);
}