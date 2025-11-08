#include <iostream>
using namespace std;

int main() {
    int indexBlock, n, blocks[100];

    cout << "Enter index block: ";
    cin >> indexBlock;

    cout << "Enter number of blocks: ";
    cin >> n;

    cout << "Enter block numbers: ";
    for(int i = 0; i < n; i++){
        cin >> blocks[i];
        if(blocks[i] == indexBlock){
            cout << "Index block and block number cannot be same!!!!! " << endl;
            return 0;
        }
    }

    cout << "Indexed Allocation:" << endl;
    cout << "Index Block: " << indexBlock << endl;
    cout << "Blocks allocated: ";
    for(int i = 0; i < n; i++)
        cout << blocks[i] << " ";

    return 0;
}
