#define SDL_MAIN_HANDLED 
#include<SDL.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<random>
#include<ranges>
#include<string>
#include<cstdlib> // for rand()
using namespace std;
void visualize(vector<int>& v, SDL_Renderer* renderer) {
	int iterate = 0;
	for (int i : v) {
		SDL_SetRenderDrawColor(renderer, 225, 153, 153, 255); // background color

		SDL_RenderDrawLine(renderer, iterate, 99, iterate, i);
			iterate++;
	}

}
void merge(vector<int>& v, int start, int end,SDL_Renderer *renderer) {
	int mid = (start + end) / 2;
	int l1 = mid - start + 1;
	int l2 = end - mid;
	vector<int> a1(l1);
	vector<int> a2(l2);
	int mainindex = start;
	for (int y = 0; y < l1; y++) {
		a1[y] = v[mainindex++];
	}
	mainindex = mid + 1;
	for (int y = 0; y < l2; y++) {
		a2[y] = v[mainindex++];
	}
	mainindex = start;
	// merge two sorted array
	int g = 0, u = 0;
	while (g < l1 && u < l2) {
		if (a1[g] < a2[u]) {
			v[mainindex++] = a1[g++];
			SDL_SetRenderDrawColor(renderer, 51, 0, 102, 225); // strips color
			SDL_RenderClear(renderer);

			// visualizing sort

			visualize(v, renderer);

			// display to screen
			SDL_RenderPresent(renderer);
			SDL_Delay(10);// delay to visualize
		}
		else {
			v[mainindex++] = a2[u++];
			SDL_SetRenderDrawColor(renderer, 51, 0, 102, 225); // strips color
			SDL_RenderClear(renderer);

			// visualizing sort

			visualize(v, renderer);

			// display to screen
			SDL_RenderPresent(renderer);
			SDL_Delay(10);// delay to visualize
		}
	}
	while (g < l1) {
		v[mainindex++] = a1[g++];
		SDL_SetRenderDrawColor(renderer, 51, 0, 102, 225); // strips color
		SDL_RenderClear(renderer);

		// visualizing sort

		visualize(v, renderer);

		// display to screen
		SDL_RenderPresent(renderer);
		SDL_Delay(10);// delay to visualize
	}
	while (u < l2) {
		v[mainindex++] = a2[u++];
		SDL_SetRenderDrawColor(renderer, 51, 0, 102, 225); // strips color
		SDL_RenderClear(renderer);

		// visualizing sort

		visualize(v, renderer);

		// display to screen
		SDL_RenderPresent(renderer);
		SDL_Delay(10);// delay to visualize
	}
}
void mergesort(vector<int>& v, int s, int e,SDL_Renderer*renderer) {
	if (s >= e) {
		return;
	}
	int m = (s + e) / 2;
	mergesort(v, s, m,renderer);
	mergesort(v, m + 1, e,renderer);
	merge(v, s, e,renderer);
}
void heapify(vector<int>&v ,int n,int i,SDL_Renderer*renderer) {
	int maxindex = i;
	int lc = 2 * i + 1;
	int rc = 2 * i + 2;

	if (lc<n && v[lc]>v[maxindex]) {
		maxindex = lc;

	}
	if (rc<n && v[rc]>v[maxindex]) {
		maxindex = rc;
	}
	if (maxindex != i) {
		swap(v[i], v[maxindex]);
		heapify(v, n, maxindex,renderer);
		// clearing the screen
		SDL_SetRenderDrawColor(renderer, 51, 0, 102, 225); // strips color
		SDL_RenderClear(renderer);

		// visualizing sort

		visualize(v, renderer);

		// display to screen
		SDL_RenderPresent(renderer);
		SDL_Delay(10);// delay to visualize
	}

}
void heapsort(vector<int>& v,SDL_Renderer*renderer) {
	int size = v.size();
	for (int i = size / 2 - 1; i >= 0; i--) {
		heapify(v, size, i,renderer);
	}
	for (int i = size - 1; i > 0; i--) {
		swap(v[0], v[i]);

		heapify(v, i, 0,renderer);
		// clearing the screen
		SDL_SetRenderDrawColor(renderer, 51, 0, 102, 225); // strips color
		SDL_RenderClear(renderer);

		// visualizing sort

		visualize(v, renderer);

		// display to screen
		SDL_RenderPresent(renderer);
		SDL_Delay(10);// delay to visualize
	}
}
int main() {
	cout << "\n---> This is the sorting visualizer made by Mandeep Singh Virdi <---\n";
	while (true) {
		vector<int> v;
		for (int i = 0; i < 100; i++) {
			int random = 1 + (rand() % 100); // generate random number from 1 to 100
			v.push_back(random);
		}
	cout << "\nFollowing are the options for the sorts that you can visualize:- ";
	cout << "\n-> Enter m for Merge Sort\n-> Enter b for Bubble Sort\n-> Enter i for Insertion Sort\n-> Enter h for Heap Sort\n-> Enter e to exit\n";
	cout << "Enter your choice: ";
	string c;
		getline(cin, c);
		if (c == "b") { // for bubble sort
			SDL_Window* window = nullptr;
			SDL_Renderer* renderer = nullptr;
			SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
			SDL_RenderSetScale(renderer, 8, 6);

			// bubble sort
			for (int i = 0; i < v.size(); i++) {
				for (int j = 0; j < v.size() - i - 1; j++) {
					if (v[j] > v[j + 1]) {
						swap(v[j], v[j + 1]);
						// clearing the screen
						SDL_SetRenderDrawColor(renderer, 51, 0, 102, 225); // strips color
						SDL_RenderClear(renderer);

						// visualizing sort

						visualize(v, renderer);

						// display to screen
						SDL_RenderPresent(renderer);
						SDL_Delay(3);// delay to visualize

					}

				}



			}
			// Now closing the screen
			SDL_DestroyRenderer(renderer);
			renderer = 0;
			SDL_DestroyWindow(window);
			window = 0;
			SDL_Quit();

		}
		else if (c == "h") { //  heap sort
			SDL_Window* window = nullptr;
			SDL_Renderer* renderer = nullptr;
			SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
			SDL_RenderSetScale(renderer, 8, 6);

			heapsort(v,renderer);
			// Now closing the screen
			SDL_DestroyRenderer(renderer);
			renderer = 0;
			SDL_DestroyWindow(window);
			window = 0;
			SDL_Quit();


		}
		else if (c == "m") {
			SDL_Window* window = nullptr;
			SDL_Renderer* renderer = nullptr;
			SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
			SDL_RenderSetScale(renderer, 8, 6);

			 // merge sort
			mergesort(v, 0, v.size()-1,renderer);
			// Now closing the screen
			SDL_DestroyRenderer(renderer);
			renderer = 0;
			SDL_DestroyWindow(window);
			window = 0;
			SDL_Quit();

		}
		else if (c == "i") {
			SDL_Window* window = nullptr;
			SDL_Renderer* renderer = nullptr;
			SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
			SDL_RenderSetScale(renderer, 8, 6);
			for (int i = 1; i < v.size(); i++) {
				int temp = v[i];
				int j = i - 1;
				for (; j >= 0; j--) {
					if (v[j] > temp) {
						v[j + 1] = v[j];
						// clearing the screen
						SDL_SetRenderDrawColor(renderer, 51, 0, 102, 225); // strips color
						SDL_RenderClear(renderer);

						// visualizing sort

						visualize(v, renderer);

						// display to screen
						SDL_RenderPresent(renderer);
						SDL_Delay(3);// delay to visualize

					}
					else {
						break;
					}
				}
				v[j + 1] = temp;

			}
			// Now closing the screen
			SDL_DestroyRenderer(renderer);
			renderer = 0;
			SDL_DestroyWindow(window);
			window = 0;
			SDL_Quit();


		}
		else if (c == "e") {
			break;
		}
		else {
			cout << "Please enter a valid choice...\n";
		}
	}


	return 0;
} 