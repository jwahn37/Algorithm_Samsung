#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
#include <string>
#include <queue>
#include <map>
#include <stack>
using namespace std;

//소스 코드 출처: https://newbrother.github.io/SWEA-1242/

/*
나랑 원리는 같은데, 소스코드가 1/3밖에 안된다는것을 중점으로 본다.
string을 이렇게 이용하는구나
*/
string bin[] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
/*
앞의 0갯수는 제외하고 타겟을 보네
*/
string target[10] = { "211","221","122","411","132","231","114","312","213","112" };

string conv(string s) {
    string re="";
    int num;
    for (int i = 0; i < s.size(); i++) {
        //16진수(str)뽑아서 2진수(str)로 바꾼다.
        if (s[i] >= 65) {
            num = s[i] - 55;
        }
        else {
            num = s[i] - '0';
        }
        re += bin[num]; //str이 이런게 쉽네. 사칙연산 가능한것.

    }
    return re;
}

int main()
{
    /*속도 증가시키는 코드 기본적으로 포함*/
    /*
    cin, cout은 scanf, printf보다 현저히 느림
    그걸 보완시켜주는 설정임
    ref: https://eine.tistory.com/entry/CC-%EC%9E%85%EC%B6%9C%EB%A0%A5-%EB%B0%A9%EB%B2%95%EC%97%90-%EB%94%B0%EB%A5%B8-%EC%86%8D%EB%8F%84-%EC%A0%95%EB%A6%AC
    https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
    */
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //freopen("a.txt", "r", stdin);

    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int ans = 0;
        ///////////////////////
        int n, m;
        cin >> n >> m;
        //암호코드 저장용(중복없애기)
        vector<string> vs;
        vector<string> univers;
        for (int i = 0; i < n; i++) {
            string str;
            cin >> str; //\n까지 받는걸로 보인다.
            int uniflag = 1;    //중복 확인 (unique한가)

            //방금 받은 input이 중복인지 통으로 확인이 쉽네.
            //하지만 구현상으로는 스트링 하나하나 비교
            //즉 코드가 쉽다고 복잡도가 낮아지진 않음
            //애당초 input때 이렇게 중복을 제거해버리면 문제가 단순해짐
            for (int u = 0; u < univers.size(); u++) {
                if (str == univers[u]) {
                    uniflag = 0;
                    break;
                }
            }
            if (uniflag==0) {
                //중복시 밑에 수행 X
                continue;
            }
            //단계별 해결이 문제를 단순화하네
            univers.push_back(str);
            //2진수로 먼저 바꾼다.
            string trans = conv(str);
            //연속된 1 개수세기
            int cnt = 0;
            int cntzero = 0;
            //vi에 갯수를 넣은것임. (0의갯수, 1의갯수, 0의갯수, ...)
            vector<int> vi;
            for (int j = 0; j < trans.size(); j++) {
                if (trans[j] != '0') {
                    vi.push_back(cntzero);
                    cntzero = 0;
                    while (j < trans.size() && trans[j] != '0') {
                        cnt++;  //1인 갯수
                        j++;
                    }
                    cntzero++;
                    vi.push_back(cnt);
                    cnt = 0;
                }
                else{
                    cntzero++;
                }
            }
            if (vi.empty()) {
                continue;
            }
            
            vector<int> numbers;
            //4개=숫자1개 , 32개=숫자8개=암호코드1개
            for (int j = 0; j <= vi.size(); j+=4) {
                if ( (j!=0 && j % 32 == 0) || j==vi.size()) {
                    string tmp = "";
                    for (int k = 0; k < numbers.size(); k++) {
                        tmp += to_string(numbers[k]);
                    }
                    int flag = 1;
                    for (int k = 0; k < vs.size(); k++) {
                        if (tmp == vs[k]) { //이미 나온 암호코드인지 중복 체크
                            flag = 0;   
                            break;
                        }
                    }
                    if (flag) {
                        vs.push_back(tmp);
                        int oddsum = 0;
                        int evensum = 0;
                        int last = numbers[7];
                        for (int k = 0; k < 7; k++) {
                            if (k % 2 == 0) {
                                oddsum += numbers[k];
                            }
                            else {
                                evensum += numbers[k];
                            }
                        }
                        int test = oddsum * 3 + evensum + last;
                        if (test % 10 == 0) {
                            ans += oddsum + evensum + last;
                        }
                    }
                    if (j == vi.size())
                        break;
                    numbers.clear();
                }
                int a = vi[j + 1];
                int b = vi[j + 2];
                int c = vi[j + 3];
                //a,b,c중 가장 작은수로 나눠준다
                //여기 오류아님?
               // int mini = min( { a, b, c } );
                int mini = min( a,b );
                mini = min( mini, c );
                a /= mini;
                b /= mini;
                c /= mini;
                //곧죽어도 스트링 연산하는게 독특
                string find = "";
                find += '0'+ a;
                find += '0' + b;
                find += '0' + c;
                //cout << find << ' ';
                for (int k = 0; k < 10; k++) {
                    if (find == target[k]) {
                        numbers.push_back(k);
                        break;
                    }
                }
            }

        }

        //////////////////////
        cout << '#' << tc << ' ' << ans << '\n';
    }
    return 0;
}
