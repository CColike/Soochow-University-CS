//Clock.java
package demo1;  

import java.awt.Color;  
import java.awt.Dimension;  
import java.awt.Graphics;  
import java.util.Calendar;  
import java.util.GregorianCalendar;  
  
import javax.swing.JPanel;  
  
public class Clock extends JPanel {  
      
    private int hour;  
    private int minute;  
    private int second;  
    @Override  
    public Dimension getPreferredSize() 
    {  
        return new Dimension(200, 200);  
    }      
    @Override  
    protected void paintComponent(Graphics g) {  
		super.paintComponent(g);
		g.setColor(Color.black);
		g.drawOval(20,20,160,160);
		g.drawString("12",95,34);
		g.drawString("3",170,103);
		g.drawString("6",97,177);
		g.drawString("9",23,103);

		int xs=(int)(100+65*Math.sin(2*Math.PI/60*second));
		int ys=(int)(100-65*Math.cos(2*Math.PI/60*second));
		int xm=(int)(100+45*Math.sin((minute+second/60)*2*Math.PI/60));
		int ym=(int)(100-45*Math.cos((minute+second/60)*(2*Math.PI/60)));
		int xh = (int)(100+35*Math.sin((hour%12+minute/60)*(2*Math.PI/12)));
		int yh = (int)(100-35*Math.cos((hour%12+minute/60)*(2*Math.PI/12)));
		
		g.drawLine(100,100,xm,ym);
		g.drawLine(100,100,xs,ys);
		g.drawLine(100,100,xh,yh); 
    }  
      
    public void setCurrentTime()
    {  
        Calendar c=new GregorianCalendar();  
        hour=c.get(Calendar.HOUR_OF_DAY);  
        minute=c.get(Calendar.MINUTE);  
        second=c.get(Calendar.SECOND);  
    }  
}  