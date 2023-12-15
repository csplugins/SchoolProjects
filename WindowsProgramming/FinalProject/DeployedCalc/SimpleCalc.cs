using System;

public class SimpleCalc : iSimpleCalc{
	public float add(float num1, float num2){
		return num1 + num2;
	}
	
	public float subtract(float num1, float num2){
		return num1 - num2;
	}
	
	public float multiply(float num1, float num2){
		return num1 * num2;
	}
	
	public float divide(float numerator, float denominator){
		return numerator / denominator;
	}
	public int mod(float num1, float num2){
		int num1Int = (int)num1;
		int num2Int = (int)num2;
		return num1Int % num2Int;
	}
	public double pow(float num, float exponent){
		if(exponent == 0)
			return 1;
		double temp = num;
		for(int i = 1; i < exponent; i++)
			temp = temp * num;
		return temp;
	}
	public double sin(float degrees){
		return (Math.Sin(Math.PI * degrees / 180.0));
	}
	public double cos(float degrees){
		return (Math.Cos(Math.PI * degrees / 180.0));
	}
	public double tan(float degrees){
		return (Math.Tan(Math.PI * degrees / 180.0));
	}
}