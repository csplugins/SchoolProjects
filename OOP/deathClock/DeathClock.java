/*
 Cody Skala (cws26)
 Programming Assignment 1 3460:421(OOP)
 Created: 9/11/2015 15:54 
 */
package deathClock;

import java.util.Calendar;
import java.util.concurrent.TimeUnit;
import java.util.GregorianCalendar;
import java.util.Scanner;

public class DeathClock {

    public static void main(String[] args) {
        int birthYear, birthMonth, birthDay;
        double yearsLeft, days;
        String date, gender;
        Scanner in = new Scanner(System.in);
        System.out.println("Enter your gender (m/f): ");
        gender = in.nextLine().trim().toLowerCase();
        if(!gender.equalsIgnoreCase("m") && !gender.equalsIgnoreCase("f")){
            System.out.println("That is an invalid option!\nExiting");
            return;
        }
        System.out.println("Enter your birth year: ");
        birthYear = in.nextInt();
        System.out.println("Enter your birth month (January = 1, February = 2, ... , December = 12): ");
        birthMonth = in.nextInt();
        if(birthMonth < 1 || birthMonth > 12){
            System.out.println("That is an invalid option!\nExiting");
            return;
        }
        System.out.println("Enter the day of the month: ");
        birthDay = in.nextInt();
        if(birthDay > 31){
            System.out.println("That is an invalid option!\nExiting");
            return;
        }

        Calendar cal = new GregorianCalendar();
        //Calendar billGatesBday = new GregorianCalendar(1955, Calendar.OCTOBER, 28);
        Calendar birthday = new GregorianCalendar(birthYear, birthMonth - 1, birthDay);
        double age = TimeUnit.MILLISECONDS.toDays(cal.getTimeInMillis() - birthday.getTimeInMillis()) / 365.25;
        System.out.println("\nYour current age is " + age);
        if(gender.equalsIgnoreCase("m"))
            yearsLeft = 0.005 * Math.pow(age, 2) - 1.265 * age + 79.554;
        else
            yearsLeft = 0.005 * Math.pow(age, 2) - 1.292 * age + 84.706;
        days = yearsLeft * 365.25;
        if (yearsLeft < 0) {
            System.out.println("You are already dead! You died " + -yearsLeft + " years ago.");
            System.out.println("That is " + -days + " days ago!");
        }
        else {
            System.out.println("You have " + yearsLeft + " years left to live!");
            System.out.println("That is " + days + " days remaining!");
        }
        cal.add(Calendar.DATE, (int)days);
        switch (cal.get(Calendar.DAY_OF_WEEK)) {
            case 1:date = "Sunday, "; break;
            case 2:date = "Monday, "; break;
            case 3:date = "Tuesday, "; break;
            case 4:date = "Wednesday, "; break;
            case 5:date = "Thursday, "; break;
            case 6:date = "Friday, "; break;
            default:date = "Saturday, ";
        }
        switch (cal.get(Calendar.MONTH)) {
            case 0:date += "January "; break;
            case 1:date += "February "; break;
            case 2:date += "March "; break;
            case 3:date += "April "; break;
            case 4:date += "May "; break;
            case 5:date += "June "; break;
            case 6:date += "July "; break;
            case 7:date += "August "; break;
            case 8:date += "September "; break;
            case 9:date += "Ovtober "; break;
            case 10:date += "November "; break;
            default:date += "December ";
        }
        date += cal.get(Calendar.DAY_OF_MONTH) + ", ";
        date += cal.get(Calendar.YEAR);
        System.out.println("Date of death: " + date);
    }
}
