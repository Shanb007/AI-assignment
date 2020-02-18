import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.*;
import java.util.LinkedList; 
import java.util.Queue; 
class UCS 
{
	static class Node
	{

		int c[][]=new int[8][8];
		int cost=0,ecost;
		int col,row;
		Node next[]=new Node[8];
		Node(int i,int j)
		{
			row=i;
			col=j;
		}

	}

	Comparator<Node>costComparator = new Comparator<Node>()
       	{
		public int  compare(Node s1, Node s2)
	       	{
			if(s1.cost==s2.cost)
				return 0;
			else if(s2.cost>s1.cost)
				return 1;
			else
				return -1;

		}
	};
	PriorityQueue<Node> queue = new PriorityQueue<>(costComparator);
	//Queue<Node> queue = new LinkedList<>(); 

	public static void main(String[]args)
	{
		Node ob1=new Node(0,0);
		UCS ob=new UCS();
		Node f=ob.findsol(0,ob1);
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				System.out.print(f.c[i][j]+" ");
			}
			System.out.println();
		}
		System.out.print(f.cost);
	}
	Node findsol(int i,Node ob)
	{

		for(int j=0;j<8&&i<8;j++)
		{

			Node ob1=new Node (i,j);
			ob.next[j]=ob1;
			for(int i1=0;i1<8;i1++)
			{
				for(int j1=0;j1<8;j1++)
				{
					ob1.c[i1][j1]=ob.c[i1][j1];
				}
			}
			ob1.c[i][j]=1;
			boolean b=check(ob1);
			if(b==true)
			{                      
				ob1.cost=ob.cost+1;

				queue.add(ob1);
			}
			else 
			{
				ob1=null;
			}
		}

		Node ob2=ob,ob1=null;
		if(queue.size()>0&&ob.row<7)
		{
			ob1=queue.poll();
			ob2=findsol(ob1.row+1,ob1);
		}
		return ob2;
	}
	boolean check(Node ob)
	{
		int c=0;
		for(int i=0;i<ob.row;i++)
		{
			for(int j=0;j<=7;j++)
			{
				if(ob.c[i][j]==1)
				{
					if((ob.row-i)==(ob.col-j)||(ob.col==j)||(ob.row-i)==(j-ob.col))
					{
						return false;
					}
				}
			}
		}
		return true;
	}
}
