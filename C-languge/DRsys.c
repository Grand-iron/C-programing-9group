#define _CRT_SECURE_NO_WARNINGS //보안 문제로 인한 오류를 방지하기 위함
#include <stdio.h>
#include <stdlib.h> // rand 함수 쓰기위해 넣음
#include <time.h>  // srand값을 랜덤으로 바꾸기 위해 넣음
#include <windows.h>

typedef struct _Student
{
	char name[20];  //이름
	char class[100]; //학과
	int number;     //학번
	int age;        //나이
	double grade;   //학점

}Student; //구조체에 별칭을 지정, 전역변수

void loading(void);  //로딩창을 보여준다.
int menu(void);      //메뉴창 출력 및 원하는 학생의 정보를 입력을 받는다.
void s_print(Student* student, char name[20], int q);  //원하는 메뉴에 맞는 답을 밑 s_로 시작하는 4개의 함수를 이용하여 출력해준다.
void s_class(Student* student, int a);    //학과 출력 
void s_num(Student* student, int a);       //학번 출력 
void s_age(Student* student, int a);       //나이 반환 
void s_grade(Student* student, int a);     //학점 반환
int main() {
boot:                                      //데이터 초기화 및 로딩창을 출력한다.
	srand((unsigned int)time(NULL));          //랜덤이 일정하지 않게 해줌
	char oryu[] = { "(오류발생)" };          //오류 발생했다는걸 알려주기 위한 문장
	int i = 0;                               //몇번을 반복할지를 정해줌	
	Student student[] = {           //구조체 배열의 초기화
		{"Kim","Computer science",2022001,20,4.1},
		{"Lee","art",2022002,21,3.8},
		{"Park","media",2022003,22,3.2},
		{"Choi","Physical Education",2022004,24,4.0},
		{"Jeong","Computer science", 2022005,60,4.5},
	};
	loading();                             //로딩한다.
	printf("현재 정보가 입력된 학생의 이름\n");   //입력된 학생들을 알려줌
	for (i = 0; i < 5; i++)
		printf("%s\n", student[i].name);
	while (1) {                                    //r_int2를 통해 25%확률로 뻑이가게 만듬 r_int는 오류 발생시 구조체 값을 랜덤으로 바꿔버림
		int changer, r_int = rand() % 99999, r_int2 = r_int % 4;
		char name[20];
		changer = menu();             //메뉴창 출력 및 메뉴에서 입력받기
		if (r_int2 == 1) {
			for (i = 0; i < 5; i++) {
				student[i].number = -r_int;
				student[i].age = -r_int;
				student[i].grade = -r_int;
				strcat(student[i].class, oryu);
			}
		}
		if (changer == 4)                     //복구프로그램 발동시 67번 줄로 이동
			break;
		else if (changer < 4 && changer >= 0) {
			printf("정보를 찾을 학생의 이름을 입력하세요 :");//학생 정보를 출력하기 전 이름을 입력받기 위함
			scanf("%s", name);
			s_print(student, name, changer);   //원하는 정보를 출력해줌.
		}
		else if (changer == 5)
			goto finish;  //프로그램 끝내기
		else {  //이상한 값 적을시 프로그램을 끝내버림
			printf("잘못된 범위의 값을 입력하셨습니다. 프로그램을 종료합니다.\n");
			goto finish;
		}
	}
	goto boot;
finish:
	printf("사용해주셔서 감사합니다.");
	Sleep(1000);  //1초간 프로그램 작동안함
	system("cls");  //화면 지우기
	return 0;
}
void loading(void) {  //로딩창
	const char bar = '='; // 프로그레스바 문자  
	const char blank = ' '; // 비어있는 프로그레스바 문자  
	const int LEN = 20; // 프로그레스바 길이  
	const int MAX = 300; // 진행작업 최대값  
	int count = 0; // 현재 진행된 작업  
	int i; // 반복문 전용 변수  
	float tick = (float)100 / LEN; // 몇 %마다 프로그레스바 추가할지 계산 
	int bar_count; // 프로그레스바 갯수 저장 변수  
	float percent; // 퍼센트 저장 변수  
	while (count <= MAX) {
		printf("\r로딩["); // 진행 상태 출력  
		percent = (float)count / MAX * 100; // 퍼센트 계산  
		bar_count = percent / tick; // 프로그레스바 갯수 계산  
		for (i = 0; i < LEN; i++) { // LEN길이의 프로그레스바 출력  
			if (bar_count > i) { // 프로그레스바 길이보다 i가 작으면 
				printf("%c", bar);
			}
			else { // i가 더 커지면  
				printf("%c", blank);
			}
		}
		printf("] %0.2f%%진행됨", percent); // 퍼센트 출력  
		count++; // 카운트 1증가  
		Sleep(10); // 퍼센트 증가 시간 조정  
	}
	Sleep(200);
	system("cls");
	printf("부팅 완료!\n\n");
	Sleep(1000);
	system("cls");
	return 0;
}
int menu(void) {
	int changer;
	printf("**************************************\n");
	printf("찾고 싶으신 데이터를 숫자로 입력해주세요. (오류날 확률 25%%)\n");
	printf("0. 학과\n");
	printf("1. 학번\n");
	printf("2. 나이\n");
	printf("3. 학점\n");
	printf("4. 오류발생시 복구 프로그램\n");
	printf("5. 종료\n");
	printf("**************************************\n");
	scanf("%d", &changer);
	return changer;
}
void s_print(Student* student, char name[20], int s_want) {
	void (*s_infomation[4])(Student * student, int) = { s_class, s_num, s_age, s_grade };
	for (int i = 0; i < 5; i++)
	{
		if (strcmp(name, student[i].name) == 0) {
			s_infomation[s_want](student, i);
		}

	}
};
void s_class(Student* student, int i) {
	printf("\n%s학생의 학과는 %s입니다.\n", student[i].name, student[i].class);
}
void s_num(Student* student, int i) {
	printf("\n%s학생의 학번은 %d입니다.\n", student[i].name, student[i].number);
}
void s_age(Student* student, int i) {
	printf("\n%s학생의 나이는 %d입니다.\n", student[i].name, student[i].age);
}
void s_grade(Student* student, int i) {
	printf("\n%s학생의 학점은 %.1lf입니다.\n", student[i].name, student[i].grade);
}