/*******************************************************************************************
 *
 *   raylib [core] example - Basic window
 *
 *   Welcome to raylib!
 *
 *   To test examples, just press F6 and execute raylib_compile_execute script
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   Example originally created with raylib 1.0, last time updated with raylib 1.0
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "../Include/raylib.h"
#include <iostream>
#include <thread>
#include <vector>
using namespace std;
// #include "../Include/gameoflife.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

constexpr const size_t screenWidth = 800u;
constexpr const size_t screenHeight = 800u;
constexpr const size_t num_rectangles = 100u;
constexpr const size_t rect_width = screenWidth / num_rectangles;
constexpr const size_t height_multiplier = screenHeight / num_rectangles;

const size_t num_algos = 6;
enum SortingAlgorithms
{
    INSERTION_SORT,
    SELECTION_SORT,
    BUBBLE_SORT,
    MERGE_SORT,
    COUNT_SORT,
    RADIX_SORT
};

string get_current_algorithm(SortingAlgorithms algo)
{
    switch (algo)
    {
    case INSERTION_SORT:
        return "Insertion Sort";
        break;
    case SELECTION_SORT:
        return "Selection Sort";
        break;
    case BUBBLE_SORT:
        return "Bubble Sort";
        break;
    case MERGE_SORT:
        return "Merge Sort";
        break;
    case COUNT_SORT:
        return "Count Sort";
        break;
    case RADIX_SORT:
        return "Radix Sort";
        break;

    default:
        return "";
        break;
    }
}

vector<int> numbers;

void initialize()
{
    numbers.clear();
    numbers.resize(num_rectangles);
    for (size_t _i = 0; _i < num_rectangles; ++_i)
    {
        numbers[_i] = _i + 1;
    }
    for (size_t _i = 0; _i < num_rectangles; _i++)
    {
        size_t _rand_pos = rand() % num_rectangles;
        swap(numbers[_i], numbers[_rand_pos]);
    }
}

SortingAlgorithms curr_algo = INSERTION_SORT;
void draw(Color _clr = BLACK)
{
    ClearBackground(RAYWHITE);
    DrawText(get_current_algorithm(curr_algo).c_str(),0,0,30,ORANGE);
    for (size_t _i = 0; _i < num_rectangles; _i++)
    {
        DrawRectangle(rect_width * _i, screenHeight - height_multiplier * numbers[_i], rect_width, height_multiplier * numbers[_i], _clr);
    }
}

void insertionSort(std::vector<int> &arr)
{
    int _n = arr.size();
    for (int _i = 1; _i < _n; _i++)
    {
        int _key = arr[_i];
        int _j = _i - 1;

        while (_j >= 0 && arr[_j] > _key)
        {
            arr[_j + 1] = arr[_j];
            _j = _j - 1;
            draw();                                                     // Visualize the array after each move
            std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Delay for visualization purposes
        }
        arr[_j + 1] = _key;
        draw();                                                     // Visualize the array after placing the key
        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Delay for visualization purposes
    }
}

void selectionSort(std::vector<int> &arr)
{
    int _n = arr.size();
    for (int _i = 0; _i < _n - 1; _i++)
    {
        int _min_idx = _i;
        for (int _j = _i + 1; _j < _n; _j++)
        {
            if (arr[_j] < arr[_min_idx])
            {
                _min_idx = _j;
            }
        }
        std::swap(arr[_i], arr[_min_idx]);
        draw();                                                     // Visualize the array after each swap
        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Delay for visualization purposes
    }
}

void bubbleSort(std::vector<int> &arr)
{
    int _n = arr.size();
    for (int _i = 0; _i < _n - 1; _i++)
    {
        for (int _j = 0; _j < _n - _i - 1; _j++)
        {
            if (arr[_j] > arr[_j + 1])
            {
                std::swap(arr[_j], arr[_j + 1]);
                draw();                                                     // Visualize the array after each swap
                std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Delay for visualization purposes
            }
        }
    }
}

void merge(std::vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
        draw();                                                     // Visualize the array after each merge step
        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Delay for visualization purposes
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
        draw();                                                     // Visualize the array after each merge step
        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Delay for visualization purposes
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
        draw();                                                     // Visualize the array after each merge step
        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Delay for visualization purposes
    }
}
void mergeSort(std::vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void menu()
{
    ClearBackground(DARKGREEN);
    for (size_t _i = 0; _i < num_algos; _i++)
    {
        string tex = to_string(_i) + ". " + get_current_algorithm(static_cast<SortingAlgorithms>(_i));
        DrawText(tex.c_str(), screenWidth / 3, screenHeight / 3 + _i * 30, 30, BLACK);
    }
}

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Sort Visualization");

    initialize();
    SetTargetFPS(20);
    bool show_menu = true, instantiated{0};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        if (show_menu)
        {
            menu();
            auto _num = GetKeyPressed();
            if (_num >= KEY_ZERO && _num <= KEY_SIX)
            {
                show_menu = false;
                curr_algo = static_cast<SortingAlgorithms>(_num - KEY_ZERO);
                cout << _num - KEY_ZERO;
            }
        }
        else
        {
            draw(); // Initial drawing of the array

            if (!instantiated)
            {
                switch (curr_algo)
                {
                case SELECTION_SORT:
                {
                    std::thread sortingThread(selectionSort, std::ref(numbers));
                    sortingThread.detach();
                }
                break;
                case BUBBLE_SORT:
                {
                    std::thread sortingThread(bubbleSort, std::ref(numbers));
                    sortingThread.detach();
                }
                break;
                case MERGE_SORT:
                {
                    std::thread sortingThread(mergeSort, std::ref(numbers), 0, num_rectangles - 1);
                    sortingThread.detach();
                }
                break;
                case INSERTION_SORT:
                {
                    std::thread sortingThread(insertionSort, std::ref(numbers));
                    sortingThread.detach();
                }
                break;

                default:

                    break;
                }
                instantiated = true;
                // std::thread sortingThread(bubbleSort, std::ref(numbers));
                // std::thread sortingThread(bubbleSort, std::ref(numbers));
                //     _instantiated = true;
                // }
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}