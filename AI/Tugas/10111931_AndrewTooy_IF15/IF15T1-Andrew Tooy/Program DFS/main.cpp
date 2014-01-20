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

//Stack Operation
int top=-1;
int stack[MAX_NODE];

void push(int item){
     // int top=-1;
     top=top+1;
     stack[top]=item;
}

int pop(){
    // int top=-1;
     int deldata=stack[top];
     top=top-1;
     return(deldata);
}

int is_stk_empty(){
    // int top=-1;
     if(top==-1)
	 return(1);
     else
	 return(0);
}

// Stack Operation

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


void DFS_traversal(){
	node *tmp;
	int N,v,start_node,status[MAX_NODE];//status arr for maintaing status.
	const int ready=1,wait=2,processed=3; //status of node.

	cout<<"Enter starting node : ";
	cin>>start_node;

	//step 1 : Initialize all nodes to ready state.
	for(int i=1;i<=totNodes;i++)
		status[i]=ready;

	//step 2 : push the start node in stack and change status.
	push(start_node); //Push starting node into stack.
	status[start_node]=wait; //change it status to wait state.

	//step 3 : Repeat until stack is empty.
	while(is_stk_empty()!=1){

		//step 4 : pop the node N of stack.
		//process N and change the status of N to
		//be processed state.
		N = pop(); //pop the node from stack.
		status[N]=processed; //status of N to processed.
		cout<<"   "<<N; //displaying processed node.

		//step 5 : push onto stack all the neighbours of N,
		//that are in ready state and change their status to
		//wait state.
		tmp = adj[N];  //for status updation.
		while(tmp!=NULL){
			v = tmp->vertex;
			if(status[v]==ready){//check status of N's neighbour.
				push(v); //push N's neighbour who are in ready state.
				status[v]=wait; //and make their status to wait state.
			}
			tmp=tmp->next;
		}
	}
}

int main(int argc, char *argv[])
{
    cout<<"*****Depth First Search Traversal*****\n";
	createGraph();
	cout<<"\n===DFS traversal is as under===\n";
    DFS_traversal();
	getch();
}
