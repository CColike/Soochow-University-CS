//Printer.java
package demo2;

import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.print.PageFormat;
import java.awt.print.Printable;
import java.awt.print.PrinterException;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.StringReader;

public class Printer implements Printable {
	private String data;

	public Printer(String s) {
		data = s;
	}
	@Override
	public int print(Graphics g, PageFormat pf, int page) throws PrinterException {
		Graphics2D g2d = (Graphics2D) g;
		int x = (int) pf.getImageableX();
		int y = (int) pf.getImageableY();
		g2d.translate(x, y);
		Font font = new Font("Serif", Font.PLAIN, 10);
		FontMetrics metrics = g.getFontMetrics(font);
		int lineHeight = metrics.getHeight();
		BufferedReader br = new BufferedReader(new StringReader(data));
		try {
			String line;
			x += 50;
			y += 50;
			while ((line = br.readLine()) != null) {
				y += lineHeight;
				g2d.drawString(line, x, y);
			}
		} catch (IOException e) {
		}
		return PAGE_EXISTS;
	}
}