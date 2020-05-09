#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <array>
#include <vector>
#include <sstream>
#include <iterator>
#include <unistd.h>
using namespace std;

int main()
{ 
    string row;
    string::size_type sz;
    map<int, vector<int>> particles;
    
    cout << "New world!" << endl;
    
    // particles vectors is: m1, m2, new, x,y 
    particles[1] = vector<int>({2, 0, 0, 400, 500});
    particles[2] = vector<int>({1, 0, 0, 600, 500});
    
    int y;
    int max;
    
    cout << "Enter how much steps you want to do:" << endl;
    cin >> max;
    y = 0;

    while (y < max) {
        y++;
        
        map<int, int> counter;
    
        for( const auto& pair : particles ) {
             int id;
             int m1;
             int m2;
             int n;
             int x;
             int y;
             int new_id;
             
             id = pair.first;
             m1 = pair.second[0];
             m2 = pair.second[1];
             x  = pair.second[3];
             y  = pair.second[4];
             
             // if new not set
             if (!pair.second[2]) {
                 n  = particles[m1][0];
                 //particles[m1][3]++;
                 counter[m1]++;
                 if (n == m1 || n == m2 || n == id) {
                     // create particle
                     new_id = particles.rbegin()->first + 1;
                     
                     int new_x = x + (rand()%2 * 2) - 1;
                     int new_y = y + (rand()%2 * 2) - 1;
                     particles[new_id] = vector<int>({id, 0, m1, new_x, new_y});
                     particles[id][2] = new_id;
                 } else {
                     // set new
                     particles[id][2] = n;
                 }
             }
        }

        cout << endl;
        cout << endl;

        int z = 0;
        int draw = 0;
        ofstream file;
        //file.open ("debug", ofstream::out | ofstream::trunc);
        file.open ("particles.svg", ofstream::out | ofstream::trunc);
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
        file << "<svg width=\"1000\" height=\"1000\" version=\"1.0\" xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;
        
        //shift
        for( const auto& pair : particles ) {
            int id;
            int m1;
            int m2;
            int n;

            id = pair.first;
            m1 = pair.second[0];
            m2 = pair.second[1];
            n  = pair.second[2];

            particles[id][0] = n;
            particles[id][1] = m1;
            particles[id][2] = 0;

            z++;
            if (counter[pair.first] > 1) {
                draw++;
                int rgb = 400-counter[pair.first];
                if (rgb < 0) rgb = 0;
                if (rgb > 200) rgb = 200;
                file << "<circle cx=\"" << pair.second[3] << "\" cy=\"" << pair.second[4] << "\" r=\"1\" fill=\"rgb("<<rgb<<","<<rgb<<","<<rgb<<")\" />" << endl;
            }
            //if (pair.second[3] > 1) {
                //file << pair.first << "=>[" << pair.second[0] << "," << pair.second[1] << "," << counter[pair.first] << "," << pair.second[3] << "," << pair.second[4] << "]" << endl;
            //}

        }

        file << "</svg>";
        file.close();
        cout << "particles update, step = " << y << " count = " << z;
        
        //sleep(1);
    }

    return 0; 
}