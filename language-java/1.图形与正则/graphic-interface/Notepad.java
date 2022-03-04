
import java.awt.*;
import javax.swing.*;

public class Notepad {
    private Notepad() {
        JFrame frame = new JFrame("Notepad");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        madeMenuBar(frame);

        JLabel yellowLabel = new JLabel();
        yellowLabel.setBackground(new Color(255, 255, 150));
        yellowLabel.setPreferredSize(new Dimension(400, 250));

        frame.getContentPane().add(yellowLabel, BorderLayout.CENTER);
        frame.pack();
        frame.setVisible(true);
    }

    private void madeMenuBar(JFrame frame) {
        JMenuBar menuBar;
        JMenu menu;
        JMenuItem menuItem;

        menuBar = new JMenuBar();
        menuBar.setOpaque(true);
        menuBar.setBackground(new Color(0, 125, 200));
        menuBar.setPreferredSize(new Dimension(400, 30));

        menu = new JMenu("File");
        menuBar.add(menu);

        menuItem = new JMenuItem("New");
        menu.add(menuItem);
        menuItem = new JMenuItem("Open");
        menu.add(menuItem);
        menuItem = new JMenuItem("Save");
        menu.add(menuItem);
        menuItem = new JMenuItem("Save as");
        menu.add(menuItem);
        menuItem = new JMenuItem("Exit");
        menu.add(menuItem);

        // Build second menu in the menu bar.
        menu = new JMenu("Edit");
        menuBar.add(menu);
        menu = new JMenu("Help");
        menuBar.add(menu);

        frame.setJMenuBar(menuBar);
    }

    public static void main(String[] args) {
        // Schedule a job for the event-dispatching thread:
        // creating and showing this application's GUI.
        new Notepad();
    }
}