#include<iostream>
#include<vector>
#include <deque>
#include<iterator>
#include<algorithm>
using namespace std;
//function to find pagefaults,hit ratio and miss ratio
void pageFaults(vector<int> pages,int n,int capacity){
    
      deque<int> q(capacity); //to store the current set of pages in memory
      deque<int>::iterator itr;
      int page_fault=0,hit_count=0;
      bool miss;
      //to print the page allocations
      cout<<"* : Miss, ^ : Hit"<<endl;
       for(int i=0;i<capacity;i++)
          {
              cout<<"f"<<i+1<<"\t";
          }
          cout<<endl; 
      for(int i=0;i<n;i++){
         miss=false;
          //check whether the current page is present in the memory
           itr=find(q.begin(),q.end(),pages[i]); 
           if(itr==q.end()) //if it's a miss (the page is not present in memory)
          {
              //increment the pagefault
              ++page_fault;
              miss=true;
              //check if the set has any empty frame
            if(q.size()==capacity)
            {
                //remove the least recently used page
                q.erase(q.begin());
                //push the current page to the dequeue
                q.push_back(pages[i]);
            }
            //if there are any empty frames then directly push the current page
            else{
                q.push_back(pages[i]);
            }
          } 
          //if it's a hit (current page is already present in memory)
          else{
             ++hit_count;
             //remove the page from its currrent position and push it at the back to account for  the recent usage of the page
             q.erase(itr);
             q.push_back(pages[i]);
          }
          for(int i=capacity-1;i>=0;i--){
              cout<<q[i]<<"\t";
             }
        (miss) ? cout<<"*":cout<<"^";
        cout<<endl;
      }
      cout<<"Total number of page faults : "<<page_fault<<endl;
      cout<<"Total number of hits : "<<hit_count<<endl;
      cout<<"Miss ratio : "<<page_fault<<"/"<<n<<" %"<<endl;
      cout<<"Hit ratio : "<<hit_count<<"/"<<n<<" %"<<endl;
}
int main(){
    int capacity,n,page;
    vector<int> pages;
    cout<<"Enter the total number of pages"<<endl;
    cin>>n;
    cout<<"Enter the list of pages"<<endl;
    for(int i=0;i<n;i++){
        cin>>page;
        pages.push_back(page);}
    cout<<"Enter the number of frames"<<endl;
    cin>>capacity;
    pageFaults(pages,n,capacity);
    return 0;
}