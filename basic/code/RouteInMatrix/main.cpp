#include <iostream>

using namespace std;
// ������12�������е�·��
// ��Ŀ�������һ�������������ж���һ���������Ƿ����һ������ĳ�ַ�������
// �ַ���·����·�����ԴӾ���������һ��ʼ��ÿһ�������ھ����������ҡ�
// �ϡ����ƶ�һ�����һ��·�������˾����ĳһ����ô��·�������ٴν���
// �ø��ӡ������������3��4�ľ����а���һ���ַ�����bfce����·����·���е���
// ĸ���»��߱�������������в������ַ�����abfb����·������Ϊ�ַ����ĵ�һ��
// �ַ�bռ���˾����еĵ�һ�еڶ�������֮��·�������ٴν���������ӡ�
// A B T G
// C F C S
// J D E H
bool hasPathCore(const char* matrix, int rows, int cols, int row,
                 int col, const char* str, int& pathLength, bool* visited)
{
    if(str[pathLength] == '\0') return true;

    bool hasPath = false;
    if(row>0 && row<rows && col>=0 && col<cols
       && matrix[row*cols + col]==str[pathLength]
       && !visited[row*cols + col])
    {
        ++pathLength;
        visited[row*cols + col] = true;
        hasPath = hasPathCore(matrix, rows, cols, row, col-1, str, pathLength, visited)
        || hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, visited)
        || hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength, visited)
        || hasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, visited);

        if(!hasPath)
        {
            --pathLength;
            visited[row*cols + col] = false;
        }
    }

    return hasPath;
}


bool hasPath(char* matrix, int rows, int cols,const char* str)
{
    if(matrix==nullptr || rows<1 || cols<1 || str==nullptr) return false;

    bool *visited = new bool[rows * cols];
//    memset(visited, 0, rows*cols);

    int pathLength = 0;
    for(int row = 0; row<rows; ++row){
        for(int col = 0; col<cols; ++col){
            if(hasPathCore(matrix, rows, cols, row, col, str, pathLength, visited))
            {
                return true;
            }
        }
    }
}


// ͨ�����ݷ��ҵ������е�·��
int main()
{
    cout << "Hello world!" << endl;
    int rows = 4;
    int cols = 4;
    char matrix[rows][cols] = {{'a','b','t','g'}
        ,   {'c','f','c','s'}
        ,   {'j','d','e','h'}};
    const char* target = "bfce";
//    const char target[] = {'b', 'f', 'c', 'e'};

    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            cout<<matrix[i][j]<<"\t";
        }
        cout<<"\n";
    }
    cout<<"target\\*target = "<<target<<"\\"<<*target<<"\tsize of target\\*target = "<<sizeof(target)<<"\\"<<sizeof(*target)<<"\n";

    bool b = hasPath(matrix, 4, 4, target);
    cout<<"b = "<<b;
    return 0;
}
