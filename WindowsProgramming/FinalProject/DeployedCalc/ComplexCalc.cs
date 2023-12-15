using System;
public class ComplexCalc : iComplexCalc{
	public cFloat add(cFloat c1, cFloat c2){
		return new cFloat(c1.getReal() + c2.getReal(), c1.getImg() + c2.getImg());
	}
	public cFloat subtract(cFloat c1, cFloat c2){
		return new cFloat(c1.getReal() - c2.getReal(), c1.getImg() - c2.getImg());
	}
	public cFloat multiply(cFloat c1, cFloat c2){
		return new cFloat(((c1.getReal()*c2.getReal())-(c1.getImg()*c2.getImg())),
			((c1.getReal()*c2.getImg())+(c1.getImg()*c2.getReal())));
	}
	public cFloat divide(cFloat c1, cFloat c2){
		return new cFloat(Convert.ToSingle((c1.getReal()*c2.getReal())+(c1.getImg()*c2.getImg())/Convert.ToSingle((c2.getReal()*c2.getReal())+(c2.getImg()*c2.getImg()))), 
				(Convert.ToSingle((c1.getImg()*c2.getReal())-(c1.getReal()*c2.getImg()))/Convert.ToSingle((c2.getReal()*c2.getReal())+(c2.getImg()*c2.getImg()))));
	}
	
}