package test5;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;

public class Chess extends JFrame
{
	JButton[][] b=new JButton[8][8];
	int status=1;
	int [][]chess;//-1 black      1 white
	
	Chess()
	{
		setLayout(new GridLayout(8,8));
		setSize(400,400);
		chess=new int[8][8];
		for(int i = 0;i < 8;i ++){
            for(int j = 0;j < 8;j ++){
                int ii = i,jj = j;
                chess[i][j] = 0;
                b[i][j] = new JButton();
                b[i][j].setVisible(true);
                b[i][j].setBackground(Color.gray);
                add(b[i][j]);
                
                b[i][j].addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e){
                	if(chess[ii][jj]==0)
                		update(ii,jj);
                }
                });    
                
                
            }
        }
		b[3][3].setBackground(Color.WHITE);
		b[3][4].setBackground(Color.BLACK);
		b[4][3].setBackground(Color.BLACK);
		b[4][4].setBackground(Color.WHITE);
		chess[3][3]=1;
		chess[3][4]=-1;
		chess[4][3]=-1;
		chess[4][4]=1;
		setTitle("黑白翻转棋");
		setVisible(true);
	}
	
	
	void update(int x,int y)
	{
		int flag=0,i=x,j=y;
		i=x;j=y;
		while(i-1>=0&&chess[i-1][j]+status==0)
		{
			i--;
		}
		if(i-1>=0&&chess[i-1][j]==status&&i!=x)
		{
			for(int k=i;k<=x;k++)
			{
				chess[k][j]=status;
				b[k][j].setBackground(status==1?Color.white:Color.BLACK);
			}
			flag=1;
		}
			
		i=x;j=y;
		while(j-1>=0&&chess[i][j-1]+status==0)
		{
			j--;
		}
		if(j-1>=0&&chess[i][j-1]==status&&j!=y)
		{
			for(int k=j;k<=y;k++)
			{
				chess[i][k]=status;
				b[i][k].setBackground(status==1?Color.white:Color.BLACK);
			}
			flag=1;
		}
		
		i=x;j=y;
		while(i+1<8&&chess[i+1][j]+status==0)
		{
			i++;
		}
		if(i+1<8&&chess[i+1][j]==status&&i!=x)
		{
			for(int k=x;k<=i;k++)
			{
				chess[k][j]=status;
				b[k][j].setBackground(status==1?Color.white:Color.BLACK);
			}
			flag=1;
		}
		
		i=x;j=y;
		while(j+1<8&&chess[i][j+1]+status==0)
		{
			j++;
		}
		if(j+1<8&&chess[i][j+1]==status&&j!=y)
		{
			for(int k=y;k<=j;k++)
			{
				chess[i][k]=status;
				b[i][k].setBackground(status==1?Color.white:Color.BLACK);
			}
			flag=1;
		}

		i=x;j=y;
		while(i-1>=0&&j-1>=0&&chess[i-1][j-1]+status==0)
		{
			i--;j--;
		}
		if(i-1>=0&&j-1>=0&&chess[i-1][j-1]==status&&i!=x)
		{
			for(int k=i,kk=j;k<=x&&kk<=y;k++,kk++)
			{
				chess[k][kk]=status;
				b[k][kk].setBackground(status==1?Color.white:Color.BLACK);
			}
			flag=1;
		}
			
		i=x;j=y;
		while(i-1>=0&&j+1<8&&chess[i-1][j+1]+status==0)
		{
			i--;j++;
		}
		if(i-1>=0&&j+1<8&&chess[i-1][j+1]==status&&i!=x)
		{
			for(int k=i,kk=j;k<=x&&kk>=y;k++,kk--)
			{
				chess[k][kk]=status;
				b[k][kk].setBackground(status==1?Color.white:Color.BLACK);
			}
			flag=1;
		}
		i=x;j=y;
		while(i+1<8&&j+1<8&&chess[i+1][j+1]+status==0)
		{
			i++;j++;
		}
		if(i+1<8&&j+1<8&&chess[i+1][j+1]==status&&i!=x)
		{
			for(int k=i,kk=j;k>=x&&kk>=y;k--,kk--)
			{
				chess[k][kk]=status;
				b[k][kk].setBackground(status==1?Color.white:Color.BLACK);
			}
			flag=1;
		}
		i=x;j=y;
		while(i+1<8&&j-1>=0&&chess[i+1][j-1]+status==0)
		{
			i++;j--;
		}
		if(i+1<8&&j-1>=0&&chess[i+1][j-1]==status&&i!=x)
		{
			for(int k=i,kk=j;k>=x&&kk<=y;k--,kk++)
			{
				chess[k][kk]=status;
				b[k][kk].setBackground(status==1?Color.white:Color.BLACK);
			}
			flag=1;
		}
			
		if(flag==1)
		{
			status=0-status;
			flag=0;
		}
	}
	
	
	public static void main(String[] args) {
        new Chess();
    }
}
