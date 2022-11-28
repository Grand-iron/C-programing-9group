#define _CRT_SECURE_NO_WARNINGS //보안 문제로 인한 오류를 방지하기 위함
#include <stdio.h>
#include <stdlib.h> // rand 함수 쓰기위함
#include <time.h>  // srand값을 랜덤으로 바꾸기 위함
#include <windows.h> //cls와 Sleep사용하기 위함
#include <string.h>  // 파일 함수 사용하기 위함
#define Five 5

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
void Make_struct(Student* student, char file_name[20]); // 공백으로 구분된 텍스트 파일의 정보를 구조체로 만들어 주는 함수 
void s_print(Student* student, char name[20], int q);  //원하는 메뉴에 맞는 답을 밑 s_로 시작하는 4개의 함수를 이용하여 출력해준다.
void s_Class(Student* student, int a);    //학과 출력 
void s_Num(Student* student, int a);       //학번 출력 
void s_Age(Student* student, int a);       //나이 반환 
void s_Grade(Student* student, int a);     //학점 반환
void Active_Active(int* Text_name); // 구조체를 만드는데 들어가는 텍스트를 바꿔준다.  이중포인터 사용
int main() {
	char* Data = "Data.txt", oryu[] = { "(오류발생)" };;
	char buffer[1001], * token;
	int i = 0, idx = 0;
	srand((unsigned int)time(NULL));          //랜덤이 일정하지 않게 해줌
	Student student[100], student_save[100];
	FILE* Data_File;
	Make_struct(student, Data);
	loading();                             //로딩한다.
boot:
	printf("현재 정보가 입력된 학생의 이름\n");   //입력된 학생들을 알려줌
	for (i = 0; i < Five; i++)
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
				Data_File = fopen(Data, "w");
				fputs("Error Error 데이터 수정 필요", Data_File);
				fclose(Data_File);
			}
		}
		if (changer == 4) {
			printf("1.Backup and Restore \n2.Active / Active \n");
			scanf("%d", &changer);
			if (changer == 1) {
				printf("프로그램을 종료합니다. 학생 데이터 파일을 수정 후 다시 실행해주세요.");
				break;
			}
			else {
				Active_Active(&Data);             //메인 밖의 함수에서 Data2 파일로 student_save 구조체를 초기화
				Make_struct(student_save, Data);
				for (i = 0; i < Five; i++) {          // student_save구조체를 이용하여 student 구조체를 초기화
					student[i] = student_save[i];
				}
				goto boot; //(goto를 써보자는 목적으로 사용).
			}
		}

		else if (changer < 4 && changer >= 0) {
			printf("정보를 찾을 학생의 이름을 입력하세요(대소문자 구분 O) :");//학생 정보를 출력하기 전 이름을 입력받기 위함
			scanf("%s", name);
			s_print(student, name, changer);   //원하는 정보를 출력해줌.
		}
		else if (changer == Five)
			goto finish;  //프로그램 끝내기 break와 같은 의미 (goto를 써보자는 목적으로 사용).
		else {  //이상한 값 적을시 프로그램을 끝내버림
			printf("잘못된 범위의 값을 입력하셨습니다. 프로그램을 종료합니다.\n");
			break;
		}
	}

finish:        //프로그램 종료 구문
	printf("사용해주셔서 감사합니다.\n");
	printf("바뀐 Data.txt 파일 원본은 Data3.txt에 새로 만들어 놨습니다."); //Data.txt와 Data2.txt 파일까지 변형되었을 경우에 복사하면 되는 복사본 생성
	FILE* Data_file;
	Data_file = fopen("Data3.txt", "w");
	fputs("Kim Computer_science 2022001 20 4.1\nLee art 2022002 21 3.8\nPark media 2022003 22 3.2\nChoi Physical_Education 2022004 24 4.0\nJeong Computer_science 2022005 60 4.5", Data_file);
	fclose(Data_file);
	Sleep(3000);  //1초간 프로그램 작동안함
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
	printf("부팅 완료!\n");
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
	void (*s_infomation[4])(Student * student, int) = { s_Class, s_Num, s_Age, s_Grade }; // 함수 포인터 배열
	int count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (strcmp(name, student[i].name) == 0) {
			s_infomation[s_want](student, i);
		}
		else
			count += 1;
		if (count == Five)
			printf("\n찾으시는 학생이 존재하지 않습니다. 초기화면으로 돌아갑니다.\n\n");
	}
};
void s_Class(Student* student, int i) {
	Student* point;
	point = &student[i];
	printf("\n%s학생의 학과는 %s입니다.\n\n", point->name, point->class);
}
void s_Num(Student* student, int i) {
	Student* point;
	point = &student[i];
	printf("\n%s학생의 학번은 %d입니다.\n\n", point->name, point->number);
}
void s_Age(Student* student, int i) {
	printf("\n%s학생의 나이는 %d입니다.\n\n", student[i].name, student[i].age);
}
void s_Grade(Student* student, int i) {
	printf("\n%s학생의 학점은 %.1lf입니다.\n\n", student[i].name, student[i].grade);
}

void Active_Active(int* Text_name) {
	int** a = &Text_name;
	printf("같은 내용이 담긴 다른 데이터 파일로 교체합니다.\n");
	**a = "Data2.txt";
}
void Make_struct(Student* student, char file_name[20]) {
	char buffer[1001], * token;
	int i = 0, idx = 0;
	FILE* Data_File;
	Data_File = fopen(file_name, "r");
	if (Data_File == NULL) {
		printf("fail to read file");
		return 0;
	}
	while (!feof(Data_File)) {
		i = 0;//i초기화

		fgets(buffer, 1001, Data_File);
		token = strtok(buffer, " "); // 
		while (token != NULL) {
			if (i == 0) {
				strcpy(student[idx].name, token);
			}
			else if (i == 1) {
				strcpy(student[idx].class, token);
			}
			else if (i == 2) {
				student[idx].number = atoi(token);
			}
			else if (i == 3) {
				student[idx].age = atoi(token);
			}
			else if (i == 4) {
				student[idx].grade = atof(token);
			}
			i++;

			token = strtok(NULL, " ");
		}
		idx++;
	}
	fclose(Data_File);
}