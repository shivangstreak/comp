class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        map<int,int>mp;
        mp[20]=9;
        mp[40]=8;
        mp[30]=99;
        mp[60]=-1;
        
        sort(stations.begin(),stations.end(), [&mp](const vector<int>&v1,const vector<int>&v2){
            return mp[v1[0]] < mp[v2[0]];
        });


        auto comp = [&mp]( const pair<int,int>& p1, const pair<int,int>& p2 ) { return mp[p1.second] < mp[p2.second]; };
        priority_queue< pair<int,int>, vector<pair<int,int>>, decltype(comp)> q(comp);
        
        for(auto x:stations){
            q.push({x[0], x[1]});
        }
        cout<<"Priority queue list :-\n";
        while(q.empty()==false){
            cout<<q.top().first<<" "<<q.top().second<<endl;
            q.pop();
        }
        return 0;
    }
};



// min heap.
// struct comp
//     {
//         bool operator()(vector<int>& a,vector<int> &b)
//         {
//             if(a[1]!=b[1])
//             {
//                 return a[1]>b[1];
//             }
            
//             return a[0]>b[0]; 
//         }
//     };
    

// priority_queue<vector<int>,vector<vector<int>>,comp> pq;


// How to sort in C++ 

//        auto comp = [&] (vector<int> &a, vector<int> &b) {
//             return a[1] < b[1];
//         };
        
//         sort(events.begin(), events.end(), comp);

// class Solution {
// public:
//     bool static comp1(const vector<int>&a,const vector<int>&b){
//        if (a[0]==b[0]){
//         return a[1]<b[1];
//        }
//        else{
//         return a[0] < b[0];
//        }
//     }

//     bool static comp2(const vector<int>&a,const vector<int>&b){
//        if (a[1]==b[1]){
//         return a[0]<b[0];
//        }
//        else{
//         return a[1] < b[1];
//        }
//     }

// int maxEnvelopes(vector<vector<int>>& envelopes) {
//     vector<vector<int>> vect1=envelopes,vect2=envelopes;

//     sort(vect1.begin(),vect1.end(),comp1);
//     vector<int> temp1=vect1[vect1.size()-1];
//     int cnt1 = 1;
//     for (int i = vect1.size()-1; i > 0; i--){
//         if(temp1[0] > vect1[i-1][0] && temp1[1] > vect1[i-1][1]){
//             cnt1++;
//         }
//         temp1 = vect1[i-1];
//     }

//     sort(vect2.begin(),vect2.end(),comp2);
//     // for(int i=0;i<vect2.size();i++){
//     //     for(int j=0;j<vect2[i].size();j++){
//     //         cout<<vect2[i][j]<<" ";
//     //     }
//     //     cout<<"\n";
//     // }

//     vector<int> temp2=vect2[vect2.size()-1];
//     int cnt2 = 1;
//     for (int i = vect2.size()-1; i > 0; i--){
//         if(temp2[0] > vect2[i-1][0] && temp2[1] > vect2[i-1][1]){
//             cnt2++;
//         }
//         temp2 = vect2[i-1];
//     }

//     return max(cnt1,cnt2);
// }
// };