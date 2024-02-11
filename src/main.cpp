#include <bits/stdc++.h>

using namespace std;

int jumlahToken, buffSize, n, m, numSeq, lenSeq, point = 0;
vector<string> token, buffer;
vector<pair<string, int>> sequences;
pair<string, int> ans = {"", 0};
vector<pair<int, int>> ansCoor;

string addSpaceString(string s){
    string ans = "";
    for(int i = 0; i < s.size(); i++){
        if(i != 0 && i%2 == 0){
            ans += " ";
        }
        ans += s[i];
    }
 
    return ans;
}

string ignoreSpaceString(string s){
    string newString = "";
    for(int i = 0; i < s.size(); i++){
        if(s[i] != ' '){
            newString += s[i];
        }
    }

    return newString;
}

void displaySequences(){
    cout << "\nSequences : \n";
    for(int i = 0; i < numSeq; i++){
        cout << i+1  << ". "<< addSpaceString(sequences[i].first) << " dengan hadiah berbobot " << sequences[i].second << "\n";
    }
}

void displayMatrix(vector<vector<pair<string, bool>>> grid){
    cout << "\nMatrix : \n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << grid[i][j].first << " ";
        }
        cout << "\n";
    }
}

void resetVis(vector<vector<pair<string, bool>>> &grid){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            grid[i][j].second = 0;
        }
    }
}

bool stringMatching(string temp, string seq){
    int n = temp.size(), m = seq.size();
    if(n < m){
        return 0;
    }

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++)
            if (temp[i + j] != seq[j])
                break;
        if (j == m) return 1;
    }
 
    return 0;
}

int getPoint(string temp){
    int ans = 0;
    for(int i = 0; i < numSeq; i++){
        if(stringMatching(temp, sequences[i].first)){
            ans += sequences[i].second;
        }
    }

    return ans;
}

void bf(vector<vector<pair<string, bool>>> &grid, int i, int j, bool vertikal, int panjang, string tempAns, vector<pair<int, int>> tempCoor){
    if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j].second) {
        return;
    }

    if(panjang == 0){
        int tempPoint = getPoint(tempAns);
        
        if(tempPoint > ans.second){
            ans.second = tempPoint;
            ans.first = tempAns;
            ansCoor = tempCoor;
        }

        return;
    }

    tempAns += grid[i][j].first;
    tempCoor.push_back({j + 1, i + 1});
    panjang--;
    grid[i][j].second = 1;
    
    if(vertikal){
        // atas
        if(i > 0){
            for(int atas = i-1; atas >= 0; atas--){
                bf(grid, atas, j, !vertikal, panjang, tempAns, tempCoor);
            }
        }
        // bawah
        if(i < n-1){
            for(int bawah = i+1; bawah < n; bawah++){
                bf(grid, bawah, j, !vertikal, panjang, tempAns, tempCoor);
            }
        }
    }else{
        // kiri
        if(j > 0){
            for(int kiri = j-1; kiri >= 0; kiri--){
                bf(grid, i, kiri, !vertikal, panjang, tempAns, tempCoor);
            } 
        }

        // kanan
        if(j < m-1){
            for(int kanan = j+1; kanan < m; kanan++){
                bf(grid, i, kanan, !vertikal, panjang, tempAns, tempCoor);
            }
        }
    }
    
    grid[i][j].second = 0;
}

void inputFile(vector<vector<pair<string, bool>>> &grid){
    string filePath;
    cout << "\nAnda memilih input menggunakan file.\n";
    cout << "\nFile yang ingin digunakan : ";
    cin >> filePath;

    // open file
    vector<string> savedText;
    string tempText;
    ifstream selFile(filePath);
    while(getline(selFile, tempText)){
        savedText.push_back(tempText);
    }

    // tutup file
    selFile.close();

    // buffer size
    buffSize = stoi(savedText[0]);

    // ukuran matrix
    string strWidth = "", strHeight = ""; // m, n
    bool pisahUkuran = false;
    for(int i = 0; i < savedText[1].size(); i++){
        if(savedText[1][i] == ' '){
            pisahUkuran = true;
        }else{
            if(!pisahUkuran){
                // kolom
                strWidth += savedText[1][i];
            }else{
                strHeight += savedText[1][i];
            }
        }
    }
    m = stoi(strWidth);
    n = stoi(strHeight);

    // matrix
    for(int i = 0; i < n; i++){
        vector<pair<string, bool>> tempGrid;

        for(int j = 0; j < m; j++){
            tempGrid.push_back({".", 0});
        }
        grid.push_back(tempGrid);
    }

    for(int i = 0; i < n; i++){
        string curRow = savedText[i + 2], newIsi = "";
        int curIndex = 0;
        for(int j = 0; j < curRow.size(); j++){
            if(curRow[j] != ' '){
                newIsi += curRow[j];
            }else{
                grid[i][curIndex].first = newIsi;
                newIsi = "";
                curIndex++;
            }
        }
        grid[i][curIndex].first = newIsi;
    }
    
    // sequences
    numSeq = stoi(savedText[n + 2]);

    for(int i = 0; i < numSeq*2; i+= 2){
        sequences.push_back({ignoreSpaceString(savedText[n + 3 + i]), stoi(savedText[n + 4 + i])});
    }
}

void inputCLI(vector<vector<pair<string, bool>>> &grid){
    cin >> jumlahToken;
    for(int i = 0; i < jumlahToken; i++){
        string x;
        cin >> x;
        token.push_back(x);
    }
    cin >> buffSize >> n >> m >> numSeq >> lenSeq;

    // buat matrix
    for(int i = 0; i < n; i++){
        vector<pair<string, bool>> tempGrid;

        for(int j = 0; j < m; j++){
            string chosen = token[rand()%jumlahToken];
            tempGrid.push_back({chosen, 0});
        }
        grid.push_back(tempGrid);
    }

    // buat sequences
    for(int i = 0; i < numSeq; i++){
        // random score
        int randScore;
        do{
            randScore = rand() % 50;
        }while(randScore == 0);

        // random sequences
        string randSeq = "";

        // pilih panjang sekuens
        int randLen;
        do{
            randLen = rand() % (lenSeq + 1);
        }while(randLen < 2);

        for(int i = 0; i < randLen; i++){
            randSeq += token[rand()%jumlahToken];
        }

        sequences.push_back({randSeq, randScore});
    }

    displayMatrix(grid);

    displaySequences();
}

int main(){
    vector<vector<pair<string, bool>>> grid;

    // INPUT

    // pilihan input
    string pilihan;
    cout << "\nPilihan input: \n";
    cout << "1. File\n";
    cout << "2. CLI\n\n";
    do{
        // validasi input
        cout << "Pilihan Anda(1/2) : ";
        cin >> pilihan;
    }while(!(pilihan == "1" || pilihan == "2"));


    // mengambil input
    if(pilihan == "1"){
        inputFile(grid);
    }else{
        inputCLI(grid);
    }

    auto start_time = chrono::high_resolution_clock::now();

    string tempAns = "";
    vector<pair<int, int>> tempCoor;

    for(int i = 0; i < m ; i++){
        bf(grid, 0, i, true, buffSize, tempAns, tempCoor);
        resetVis(grid);
    }
    
    auto end_time = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

    // output
    string savedAnswer = "";

    cout << "\n" << ans.second << "\n";
    savedAnswer += to_string(ans.second);
    savedAnswer += "\n";

    if(ans.second != 0){
        cout << addSpaceString(ans.first) << "\n";
        savedAnswer += addSpaceString(ans.first);
        savedAnswer += "\n";
        for(int i = 0; i < buffSize; i++){
            cout << ansCoor[i].first << ", " << ansCoor[i].second << "\n";
            savedAnswer += to_string(ansCoor[i].first);
            savedAnswer += ", ";
            savedAnswer += to_string(ansCoor[i].second);
            savedAnswer += "\n";
        }
    }
    
    cout << "\n\n";
    savedAnswer += "\n\n";

    cout << duration.count() << " ms\n\n\n";
    savedAnswer += to_string(duration.count());
    savedAnswer += " ms";

    // write to file
    do{
        cout << "Apakah ingin menyimpan solusi? (y/n)\n";
        cin >> pilihan;
    }while(!(pilihan == "y" || pilihan == "n"));
    
    if(pilihan == "y" || pilihan == "Y"){
        cout << "\nFile yang ingin digunakan : ";
        string solFile;
        cin >> solFile;

        ofstream outputFile("./test/" + solFile, ios::trunc);
        if(!outputFile.is_open()){
            cout << "Gagal membuka file.";
            return 1;
        }

        outputFile << savedAnswer;

        outputFile.close();

        cout << "\nSolusi telah tertulis pada file ./test/" << solFile << ".\n\nTerima kasih.\n";
    }

    return 0;
}