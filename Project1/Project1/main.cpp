#include "main.h"

typedef struct {
	int rank;
	int val;
	int t_data[TYPE];
} data;

void reset(data* mydata);		//! 構造体初期化
void i_ran(data* my_data);		//! 乱数格納
void rank(data* my_data);		//! val付け
void sort(data* my_data);		//! valのソート（降順）
void change(data* my_data);		//! 掛け合わせ

void main(void) {

	data mydata[ARRAY];			//! 構造体実体生成

	reset(mydata);				//! 初期化
	
	i_ran(mydata);				//! 乱数格納

	for (int loop = 0; loop < 200; loop++) {

		rank(mydata);				//! rank付け
		sort(mydata);				//! ソート

/*		for (int i = 0; i < ARRAY; i++) {
			printf("rank:%d val%02d：", mydata[i].rank, mydata[i].val);
			for (int j = 0; j < TYPE; j++) {
				printf("%d", mydata[i].t_data[j]);
			}
			printf("\n");
		}*/

		change(mydata);				//! 掛け合わせ
	}

	for (int i = 0; i < ARRAY; i++) {
		printf("rank:%d val:%04d：", mydata[i].rank, mydata[i].val);
		for (int j = 0; j < TYPE; j++) {
			printf("%d", mydata[i].t_data[j]);
		}
		printf("\n");
	}

	system("pause");

}

/** 構造体初期化
*/
void reset(data* mydata) {

	//! 二次元配列の初期化
	for (int i = 0; i < (sizeof(mydata) / sizeof(mydata[0])); i++)
	{
		mydata[i].rank = 0;
		mydata[i].val = 0;
		for (int j = 0; j < TYPE; j++) {
			mydata[i].t_data[j] = 0;
		}
	}

}

/**
* @fn void i_ran()
* @brief 乱数を二次元配列び格納
* @return void なし
* @details 乱数の格納
*/
void i_ran(data* my_data) {
	//乱数
	srand((unsigned)time(NULL));

	//乱数格納
	for (int i = 0; i < ARRAY; i++) {
		for (int j = 0; j < TYPE; j++) {
			my_data[i].t_data[j] = rand() % 2;
		}
	}
}

void rank(data* my_data) {

	//! 重みと価値配列　
	int weight[TYPE] = { 2,  4, 6,   1,   8,   9,  10,   1 };
	int price[TYPE] = { 100, 10, 5, 100, 200, 150, 300, 500 };

	//!重さリミット比較
	int w_temp = 0;
	int p_temp = 0;

	for (int i = 0; i < ARRAY; i++) {
		for (int j = 0; j < TYPE; j++) {
			w_temp += my_data[i].t_data[j] * weight[i];
			if (my_data[i].t_data[j] == 1) {
				p_temp += weight[i] * price[i];
			}
		}
		if (w_temp < LIMIT) {
			my_data[i].val = p_temp;
		}
		else {
			my_data[i].val = 0;
		}
		w_temp = 0;
	}
}

void sort(data* my_data) {

	data temp;

	for (int i = 0; i< ARRAY; i++) {
		for (int j = ARRAY - 1; j > i; j--) {
			if (my_data[j].val > my_data[j - 1].val) {
				memcpy(&temp, &my_data[j], sizeof(data));
				memcpy(&my_data[j], &my_data[j-1], sizeof(data));
				memcpy(&my_data[j-1], &temp, sizeof(data));
			}
		}
	}
	for (int i = 0; i < ARRAY; i++) {
		my_data[i].rank = i+1;
	}
}

void change(data* my_data) {

		//! rank1位とrank2位の上位と下位rank3位に格納
	for (int i = 0; i < TYPE/2; i++) {
		my_data[2].t_data[i] = my_data[0].t_data[i];
		my_data[3].t_data[i] = my_data[1].t_data[i];
	}
	for (int i = TYPE - 1; i >= TYPE / 2; i--) {
		my_data[2].t_data[i] = my_data[1].t_data[i];
		my_data[3].t_data[i] = my_data[0].t_data[i];
	}

}
