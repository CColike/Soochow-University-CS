package demo1;

public class Encode {
	//first  step:rr<-r1<-r2<-r3<-'data'
	//second step:rr->r1->r2->r3->answer
	
	private int num1,num2,num3,cnt1,cnt2,cnt3;
	private Ratator r1,r2,r3;
	private Reflector rr;
	private String res;
	
	private void init_ratator()
	{
		for(int i=1;i<=num1;i++)
			r1.ratate();
		for(int i=1;i<=num2;i++)
			r2.ratate();
		for(int i=1;i<=num3;i++)
			r3.ratate();
		cnt1=num1%26;
		cnt2=num2%26;
		cnt3=num3%26;
	}
	
	private void roll()
	{
		cnt3++;
		r3.ratate();
		if(cnt3==26)
		{
			cnt2++;
			r2.ratate();
			cnt3=0;
		}
		if(cnt2==26)
		{
			cnt1++;
			r1.ratate();
			cnt2=0;
			cnt1/=26;
		}
	}
	
	public String get_res()
	{
		return res;
	}
	
	Encode(int n1,int n2,int n3,String s)
	{
		num1=n1;num2=n2;num3=n3;
		int []l1={15,7,16,6,20,12,4,0,24,11,13,5,3,23,8,17,2,21,18,1,22,10,14,25,19,9};
		int []l2={15,17,4,6,23,13,21,24,18,19,12,22,2,16,8,10,5,25,0,11,3,14,1,9,20,7};
		int []l3={22,16,13,17,15,12,23,20,9,11,14,21,0,7,18,2,1,10,5,25,19,3,24,8,6,4};
		int []lr={1,0,3,2,5,4,7,6,9,8,11,10,13,12,15,14,17,16,19,18,21,20,23,22,25,24};//special
		
		r1=new Ratator(l1);r2=new Ratator(l2);r3=new Ratator(l3);
		rr=new Reflector(lr);
		
		init_ratator();

		cnt1=0;cnt2=0;cnt3=0;
		res=new String();
		for(int i=0;i<s.length();i++)
		{
			int temp=r1.get(r2.get(r3.get(s.charAt(i)-'a')));
			temp=rr.get(temp);
			temp=r3.back(r2.back(r1.back(temp)));
			roll();
			res=res+(char)(temp+'a');
		}
	}
}
