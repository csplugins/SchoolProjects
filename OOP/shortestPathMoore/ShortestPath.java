package shortestPath;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;
import java.util.Stack;
import java.util.ArrayDeque;
import	java.awt.*;
import	java.awt.event.*;
import	javax.swing.*;
import	javax.swing.border.*;

/**
 * OOP Fall 2015 Project 4
 * @author Cody Skala (cws26)
 * date: 4:10PM 11/11/2015
 * This program will open a .dat file containing a list of vectors(Cities)
 * and an edge(distance) connecting the cities and determine the shortest path
 * from a starting city to another city. The path may need to be changed but
 * currently works for Netbeans. The display uses a simple GUI.
 */
public class ShortestPath {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new FileReader("nqmqBig.dat"));
        final int n = in.nextInt();
        final City[] cities = new City[n];
        final int[][] adjacentMatrix = new int[n][n];
        for(int i = 0; i < n; i++){
            cities[i] = new City(in.next(), i);
        }
        int temp = in.nextInt();
        int temp2 = in.nextInt();
        while(temp != -1){
            adjacentMatrix[temp][temp2] = in.nextInt();
            adjacentMatrix[temp2][temp] = adjacentMatrix[temp][temp2];
            temp = in.nextInt();
            temp2 = in.nextInt();
        }
        
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(adjacentMatrix[i][j] == 0)
                   adjacentMatrix[i][j] = Integer.MAX_VALUE;
        
        final ArrayDeque<City> ADC= new ArrayDeque<>();
        
        JFrame frame = new JFrame();
        final JComboBox<String> facenameCombo = new JComboBox<>();
        final JComboBox<String> facenameCombo2 = new JComboBox<>();
        JButton calculateButton = new JButton("Display");
        final JTextArea sampleField = new JTextArea("Select two cities\n"
                + "to see shortest path\nand the total distance.",8, 1);
        ActionListener listener;
        frame.add(sampleField, BorderLayout.CENTER);
        for(int i = 0; i < n; i++){
            facenameCombo.addItem(cities[i].getName());
            facenameCombo2.addItem(cities[i].getName());
        }
        facenameCombo.setEditable(true);
        facenameCombo2.setEditable(true);
        sampleField.setFont(new Font("Arial", 1, 14));
        class ChoiceListener implements ActionListener {
            @Override
            public void actionPerformed(ActionEvent event) {
                sampleField.setText("** " + facenameCombo.getSelectedItem()
                +" to " + facenameCombo2.getSelectedItem() + " **\n\nPath:\n");
                for(int i = 0; i < n; i++){
                    cities[i].reset();
                }
                ADC.add(cities[facenameCombo.getSelectedIndex()]);
                cities[facenameCombo.getSelectedIndex()].setDist(0);
                while (!ADC.isEmpty()) {
                    City tempCity = ADC.remove();
                    for (int j = 0; j < n; j++) {
                        if (adjacentMatrix[tempCity.getIndex()][j] != Integer.MAX_VALUE) {
                            int newDist = tempCity.getDist() + adjacentMatrix[tempCity.getIndex()][j];
                            if (newDist < cities[j].getDist()) {
                                cities[j].setDist(newDist);
                                cities[j].setPrevCity(tempCity);
                                ADC.add(cities[j]);
                            }
                        }
                    }
                }

                Stack<City> SC = new Stack<>();
                SC.push(cities[facenameCombo2.getSelectedIndex()]);
                boolean testForPrevCity = true;
                while (testForPrevCity) {
                    if (SC.peek().getPrev() == null) {
                        testForPrevCity = false;
                    } else {
                        SC.push(SC.peek().getPrev());
                    }
                }
                City tempCity = SC.firstElement();
                int count = 1;
                while(!SC.isEmpty()){
                    sampleField.setText(sampleField.getText() + count + ". " + SC.pop().getName() + "\n");
                    count++;
                }
                sampleField.setText(sampleField.getText() + "\nTotal Distance:\n" + tempCity.getDist());
            }
        }
        listener = new ChoiceListener();
        calculateButton.addActionListener(listener);
        JPanel panel = new JPanel();
        panel.add(facenameCombo);
        panel.add(facenameCombo2);
        panel.add(calculateButton);
        panel.setBorder(new TitledBorder(new EtchedBorder(), "Path & Distance"));
        JPanel facenamePanel = panel;
        JPanel controlPanel = new JPanel();
        controlPanel.setLayout(new GridLayout(1, 1));
        controlPanel.add(facenamePanel);
        frame.add(controlPanel, BorderLayout.NORTH);
        frame.setSize(400, 400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);

    }
}

class City{
    private final String name;
    private final int index;
    private int shortestPath;
    private City previousCity;
    City(String city, int ind){
        name = city;
        index = ind;
        shortestPath = Integer.MAX_VALUE;
        previousCity = null;
    }
    String getName(){
        return name;
    }
    
    int getIndex(){
        return index;
    }
    
    City getPrev(){
        return previousCity;
    }
    
    int getDist(){
        return shortestPath;
    }
    
    void setDist(int d){
        shortestPath = d;
    }
    
    void setPrevCity(City c){
        previousCity = c;
    }
    
    void reset(){
        shortestPath = Integer.MAX_VALUE;
        previousCity = null;
    }
}