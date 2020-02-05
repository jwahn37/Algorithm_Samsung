#include<iostream>

using namespace std;

#define MAX_HEIGHT (2000)
#define MAX_WIDTH (500)
#define LEN_CODE (8)
int T;
int N, M;
char code_map[MAX_HEIGHT][MAX_WIDTH];
/*
const char code_bin[10][7]= { {'0','0','0','1','1','0','1'}, //0
						{'0','0','1','1','0','0','1'}, //1
						{'0','0','1','0','0','1','1'}, //2
						{'0','1','1','1','1','0','1'}, //3
						{'0','1','0','0','0','1','1'}, //4
						{'0','1','1','0','0','0','1'}, //5
						{'0','1','0','1','1','1','1'}, //6
						{'0','1','1','1','0','1','1'}, //7
						{'0','1','1','0','1','1','1'}, //8
						{'0','0','0','1','0','1','1'} };
*/
const char code_ratio_bin[10][4]= { {3,2,1,1}, //0
									{2,2,2,1}, //1
									{2,1,2,2}, //2
									{1,4,1,1}, //3
									{1,1,3,2}, //4
									{1,2,3,1}, //5
									{1,1,1,4}, //6
									{1,3,1,2}, //7
									{1,2,1,3}, //8
									{3,1,1,2} }; //9
char code_ratio[4];
int code_val[LEN_CODE];

void init_codemap();
void init_codeval();
void init_coderatio();
int solve();
char can_be_code(const int h, const int w);
//int extract_code(const int h, int w);
int extract_code(const int height, const int width, const int bitidx);

void extract_first_ratio(const int height, const int width, const int bitidx);
int convert_to_decimal(const int val_idx);
int code_verify();
char extract_codeval(const int height, const int width, const int bitidx);

//1. 코드는 모듈화시켜서 보기 좋게 -> 검토할때 효율적

int main()
{
	int t;
	int h,w;
	cin>>T;
	for(t=1; t<=T; t++)
	{
		//초기화
		init_codemap();

		cin>>N>>M;
		for(h=0; h<N; h++)
		{
			for(w=0; w<M; w++)
			{
				cin>>code_map[h][w];
				//if(h==0 && w==0)	cout<<"DEBUG "<<code_map[h][w]<<endl;
			}
		}
/*
		for(h=0; h<N; h++)
		{
			for(w=0; w<M; w++)
			{
				//cin>>code_map[h][w];
				cout<<code_map[h][w];
			}
			cout<<endl;
		}
		*/
		cout<<"#"<<t<<" "<<solve()<<endl;
	}
}

int solve()
{
	int h,w,i;
	int res;

	//0. 초기화
	//code_val
	//init_codeval();

	//1. 전탐색
	res=0;
	for(h=0; h<N; h++)
	{
		for(w=0; w<M; w++)
		{
		//	cout<<"("<<h<<","<<w<<")"<<endl;
		//	res=0;
			//2.암호코드가 존재할 가능성 여부 체크
			//현재 인덱스는 최초 1이 등장하는 16진수임
			if(can_be_code(h, w))
			{
				for(i=0; i<4; i++)
				{
					//올바른 초기화 시점
					init_codeval();
					res=0;
				//cout<<"("<<h<<","<<w<<")"<<endl;
				//3. 코드 탐색하며 암호코드 추출하기
				//h, w에서 있을수 있는 가능성은 해당 함수 내에서 무조건 다 체크하기
					if(extract_codeval(h,w,i))
					{
						res+=extract_code(h, w, i);
						if(res != 0)	return res;
					}
				}
			}
		}
	}
	return res;
	//	return 0;
}

char can_be_code(const int h, const int w)
{	
//	cout<<"canbecode "<<h<<" "<<w<<" "<<code_map[h][w]<<endl;
	if(code_map[h][w]!='0')	return 1;
	else	return 0;
}

int extract_code(const int height, const int width, const int bitidx)
{
	int h, w, i;
	char cur_v, comp_v;
	int ratio_idx;
	int val_idx;
	int code_len, code_len_new;
	char flag_i;
	//cout<<"DEBUG: hwi: "<<height<<" "<<width<<" "<<bitidx<<endl;

	h=height, w=width, i=bitidx;
	val_idx=0;
	flag_i=1;

//	cout<<"DEBUG hwi "<<h<<" "<<w<<" "<<bitidx<<endl;
	cur_v = extract_codeval(h,w,i);
//	cout<<"DEBUG cur_v "<<(int)cur_v<<endl;
	ratio_idx = 1;	//초반 0들은 건너뛰고 시작함.
	//비는 1:1:1:1로 초기화
	init_coderatio();
	//0의 비는 건너 뛰고 시작했으므로, 이전 0이 몇개인지 조사
	//0의갯수:1의갯수:0의갯수:1의갯수 비를 구하는 것이 목적이고
	//첫번째 0의 갯수는 MAX값임
	extract_first_ratio(height, width, bitidx);

	for(; w<M; w++)
	{
		//i는 초반에만 bitidx고 이후 루프에서는 0부터 시작해야함.
		//i 초기화 문제가 생각보다 더 복잡하다는 것을 깨달음..
		//하는 수없이 flag로 i 초기화값을 판단
		for(i=((w==width)? bitidx: 0); i<4; i++)
		{
			flag_i = 0;
			//초반 비교는 건너뛴다..
			if(h==height && w==width && i==bitidx)	continue;
			
			comp_v = extract_codeval(h,w,i);
		//	cout<<"DEBUG cur_v, comp_v "<<(int)cur_v<<" "<<(int)comp_v<<endl;
		//	cout<<"DEBUG hwi "<<h<<" "<<w<<" "<<i<<endl;
			//기준값과 비교값이 같다면?
			if(cur_v == comp_v)
			{
				code_ratio[ratio_idx]++;
			}
			//기준값이 비교값과 다르다면?
			else
			{
				ratio_idx++;
				cur_v = comp_v;
				
				//cout<<"DEBUG ratio idx "<<ratio_idx<<endl;
				//코드 값 하나 추출
				if(ratio_idx >= 4)
				{
					//code길이를 알아야함
					if(val_idx==0)
					{
						code_len = convert_to_decimal(val_idx);
						if(code_len == -1)
						{
							//cout<<"DEBUG code_len -1"<<endl;
							//잘못된 코드
							return 0;
						}
					}
					else
					{
						code_len_new = convert_to_decimal(val_idx);
						//코드 길이는 다 같아야함
						if(code_len_new != code_len)
						{
							//잘못된 코드
							//cout<<"DEBUG code_len not matched"<<endl;
							return 0;
						}
						if(code_len_new==-1)
						{
							//cout<<"DEBUG code_len -1"<<endl;
							return 0;
						}
					}
					
					val_idx++;	
					//코드 다 뽑아냈는지 확인
					if(val_idx>=LEN_CODE)
					{
						//cout<<"DEBUG code verify executed?"<<endl;
						return code_verify();
					}
					
					//다음 체크를 위한 초기화
					//비는 1:1:1:1로 초기화
					init_coderatio();
				//	extract_first_ratio(height, width, bitidx);
				//	ratio_idx=1;
				//	flag_i=1;
					ratio_idx=0;
				}
			}
		}
	}
	//한줄이 끝나도록 코드를 못찾았으면
//	while(1);
	return 0;
}

//0의 최대 갯수를 리턴한다. (즉 첫번쨰 비는 MAX임)
void extract_first_ratio(const int height, const int width, const int bitidx)
{
	int i, w;
	int zero_cnt=0;
	int flag_b;


	for(w=width; w>=0; w--)
	{
		flag_b=0;
		for(i = (w==width)?bitidx:3; i>=0; i--)
		{
			//이전 인덱스부터 시작해야함
			if(width==w && i==bitidx)	continue;
			
			if(extract_codeval(height, w, i) == 0)
				zero_cnt++;
			else
			{
				flag_b=1;
				break;
			}
		}
		if(flag_b==1)	break;
	}
	code_ratio[0] = zero_cnt;
	//cout<<"DEBUG code_ratio: "<<zero_cnt<<endl;
	return;
}

//현재 비를 계산하여 숫자 추출 + 총 비율의 길이도 리턴하자.
/*
	code_ratio는 (MAX):?:?:? 비로 존재
	따라서 ?:?:?를 보고 값을 유추한후, (MAX)가 충분한지 확인할것임
*/	
int convert_to_decimal(const int val_idx)
{
	int code_len;
	int i,j;
	int K;

//	cout<<"DEBUG: ratio: "<<(int)code_ratio[0]<<" "<<(int)code_ratio[1]<<" "<<(int)code_ratio[2]<<" "<<(int)code_ratio[3]<<endl;
//	while(1);
	
	for(i=0; i<10; i++)
	{
		//두번쨰 비가 나누어 떨어지는지 확인
		for(j=0; j<3; j++)
		{
			if(code_ratio[j] % code_ratio_bin[i][j] != 0)	
				continue;
		}
		//모든 비가 K로 일정한지 확인
		K = code_ratio[1] / code_ratio_bin[i][1];
		if(code_ratio[2] / code_ratio_bin[i][2] != K)	continue;	
		if(code_ratio[3] / code_ratio_bin[i][3] != K)	continue;	
	
		//첫번쨰 인덱스(MAX)가 충분한지 확인
		if(code_ratio[0] < code_ratio_bin[i][0]*K)	continue;
	
		//숫자 구해서 리턴
		code_len = 0;
		for(j=0; j<4; j++)
			code_len += code_ratio_bin[i][j];
		code_len *= K;
	
		//cout<<"DEBUG: ratio: "<<(int)code_ratio[0]<<" "<<(int)code_ratio[1]<<" "<<(int)code_ratio[2]<<" "<<(int)code_ratio[3];
		//cout<<" i "<<i;
		//cout<<" codelen "<<code_len<<" "<<K<<endl;

		//while(1);
	
		code_val[val_idx] = i;
		return code_len;
	}

	return -1;
}

//code_val에 뽑힌 코드 증명 후 합을 리턴하자.
int code_verify()
{
	int i;
	int res;
	int check_val;

	check_val=0;
	res=0;

	for(i=0; i<LEN_CODE; i++)
	{
		//cout<<"DEBUG: "<<code_val[i]<<endl;
		//(i+1)이 홀수자
		if(((i+1)&1)==1)
		{
			check_val += code_val[i]*3;
			res += code_val[i];
		}
		//짝수자리
		else if(((i+1)&1)==0)
		{
			check_val += code_val[i];
			res += code_val[i];
		}
	}

	if(check_val%10==0)
		return res;

	return 0;
}

char extract_codeval(const int height, const int width, const int bitidx)
{
	int codeval;

	//문자형을 정수형으로 변형
	if(code_map[height][width]>='0' && code_map[height][width]<='9')
		codeval = code_map[height][width]-'0';
	//대문자들만 있을걸로 예상
	switch(code_map[height][width])
	{
		case 'A': codeval = 0xA;	break;
		case 'B': codeval = 0xB;	break;
		case 'C': codeval = 0xC;	break;
		case 'D': codeval = 0xD;	break;
		case 'E': codeval = 0xE;	break;
		case 'F': codeval = 0xF;	break;
	}
	//cout<<"DEBUG extractcodeval: "<<bitidx<<" "<<code_map[height][width]<<" "<<codeval<<" "<<((codeval>>(3-bitidx))&1)<<endl;
	//cout<<"DEBUG hwi: "<<height<<" "<<width<<" "<<bitidx<<endl;
	return (codeval>>(3-bitidx)) & 1;
}

void init_codemap()
{
	int h,w;
	for(h=0; h<50; h++)
	{
		for(w=0; w<100; w++)
		{
			code_map[h][w]=0;
		}
	}
}

void init_codeval()
{
	int i;
	for(i=0; i<LEN_CODE; i++)
		code_val[i]=0;
}

void init_coderatio()
{
	int i;
	for(i=0; i<4; i++)
	{
		code_ratio[i] = 1;	//비는 최소 1임
	}
}
