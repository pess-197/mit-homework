//#include <iostream>
//#include <cmath>
//using namespace std;
//
//void print(long double *arr, int n) {
//	long double sum=0;
//	for (int i = 0; i < n; i++) {
//		sum +=  arr[i];
//	}
//	for (int i = 0; i < n; i++) {
//		cout << "Party " << i + 1 << ": " << arr[i] << " (" << (arr[i]/sum)*100 << "%)" << endl;
//	}
//}
//
//int main() {
//	int seat_num = 0;
//	cout << "Enter the number of seats to be filled: ";
//	cin >> seat_num;
//	int seat_num1 = seat_num;
//	int party_num = 0;
//	cout << "Enter the number of parties: ";
//	cin >> party_num;
//	long double* votes = new long double[party_num];
//	long double* extra_votes = new long double[party_num];
//	long double* extra_votes1 = new long double[party_num];
//	for (int i = 0; i < party_num; i++) {
//		cout << "Enter the number of votes for Party " << i + 1 << ": ";
//		cin >> votes[i];
//		extra_votes[i] = votes[i];
//		extra_votes1[i] = votes[i];
//	}
//	cout << '\n';
//	print(votes, party_num);
//	long double* seats = new long double[party_num];
//	long double* seats1 = new long double[party_num];
//	for (int i = 0; i < party_num; i++) {
//		seats[i] = 0;
//	}
//	for (int i = 0; i < party_num; i++) {
//		seats1[i] = 0;
//	}
//	long double maxx = 0;
//	int max_x = -1;
//	long double maxx1 = 0;
//	int max_x1 = -1;
//	while (seat_num > 0) {
//		for (int i = 0; i < party_num; i++) {
//			if (extra_votes[i] > maxx) {
//				maxx = extra_votes[i];
//				max_x = i;
//			}
//			if (extra_votes1[i] > maxx1) {
//				maxx1 = extra_votes1[i];
//				max_x1 = i;
//			}
//		}
//		seats[max_x]++;
//		extra_votes[max_x] = votes[max_x] / (2 * seats[max_x] + 1);
//		seat_num--;
//		maxx = 0;
//		max_x = -2;
//		seats1[max_x1]++;
//		extra_votes1[max_x1] = votes[max_x1] / (seats1[max_x1] + 1);
//		seat_num1--;
//		maxx1 = 0;
//		max_x1 = -2;
//	}
//	cout << '\n';
//	cout << "Sainte-Lague method: " << endl;
//	cout << '\n';
//	print(seats, party_num);
//	cout << '\n';
//	cout << "D'Hondt method: " << endl;
//	cout << '\n';
//	print(seats1, party_num);
//}