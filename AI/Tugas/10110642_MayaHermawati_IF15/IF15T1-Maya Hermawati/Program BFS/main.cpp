#include <cstdlib>
#include <iostream>
#include <conio.h>
#define MAX_NODE 50

using namespace std;

struct node{
	int vertex;
	node *next;
};

node *adj[MAX_NODE]; //For storing Adjacency list of nodes.
int totNodes; //No. of Nodes in Graph.

////////////Queue Operation
int queue[MAX_NODE],f=-1,r=-1;

void q_insert(int item){
     //int queue[MAX_NODE],f=-1,r=-1;
	r = r+1;
	queue[r]=item;
	if(f==-1)
	   f=0;
}

int q_delete(){
    //int queue[MAX_NODE],f=-1,r=-1;
    int delitem=queue[f];
    if(f==r)
       f=r=-1;
    else
       f=f+1;
    return(delitem);
}

int is_q_empty(){
    //int f=-1;
    if(f==-1)
      return(1);
    else
      return(0);
}
////////////Queue Operation\\\\\\\\\\\\\

void createGraph(){
	node *newl,*last;
	int neighbours,neighbour_value;
	cout<<"\n\n---Graph Creation---\n\n";
	cout<<"Enter total nodes in graph : ";
	cin>>totNodes;
	for(int i=1;i<=totNodes;i++){
		last=NULL;
		cout<<"\nEnter no. of nodes in the adjacency list of node "<<i<<"\n";
		cout<<"--> That is Total Neighbours of "<<i<<" : ";
		cin>>neighbours;
		for(int j=1;j<=neighbours;j++){
			cout<<"Enter neighbour #"<<j<<" : ";
			cin>>neighbour_value;
			newl=new node;
			newl->vertex=neighbour_value;
			newl->next=NULL;
			if(adj[i]==NULL)
				adj[i]=last=newl;
			else{
				last->next = newl;
				last = newl;
			}
		}
	}
}


void BFS_traversal(){
	node *tmp;
	int N,v,start_node,status[MAX_NODE];//status arr for maintaing status.
	const int ready=1,wait=2,processed=3; //status of node.

	cout<<"Enter starting node : ";
	cin>>start_node;

	//step 1 : Initialize all nodes to ready state.
	for(int i=1;i<=totNodes;i++)
		status[i]=ready;

	//step 2 : put the start node in queue and change status.
	q_insert(start_node); //Put starting node into queue.
	status[start_node]=wait; //change it status to wait state.

	//step 3 : Repeat until queue is empty.
	while(is_q_empty()!=1){

		//step 4 : Remove the front node N of queue.
		//process N and change the status of N to
		//be processed state.
		N = q_delete(); //remove front node of queue.
		status[N]=processed; //status of N to processed.
		cout<<"   "<<N; //displaying processed node.

		//step 5 : Add to rear of queue all the neighbours of N,
		//that are in ready state and change their status to
		//wait state.
		tmp = adj[N];  //for status updation.
		while(tmp!=NULL){
			v = tmp->vertex;
			if(status[v]==ready){//check status of N's neighbour.
				q_insert(v); //insert N's neighbour who are in ready state.
				status[v]=wait; //and make their status to wait state.
			}
			tmp=tmp->next;
		}
	}
}



int main(int argc, char *argv[])
{
    cout<<"*****Breadth First Search Traversal*****\n";
	createGraph();
	cout<<"\n===BFS traversal is as under===\n";
	BFS_traversal();
    getch();
}

