package ks2027405033;
import java.io.File;

//主类
public class Main {
	// 文件路径
	public static final String inFile = System.getProperty("user.dir") + File.separator + "product.txt";
	public static final String outFile = System.getProperty("user.dir") + File.separator + "result.txt";

	public static void main(String[] args) {
		// 创建文件对象
		File in = new File(inFile);
		File out = new File(outFile);
		new FrmProduct(in, out);  // 启动GUI
	}

}