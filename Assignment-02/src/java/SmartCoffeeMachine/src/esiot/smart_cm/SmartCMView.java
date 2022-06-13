package esiot.smart_cm;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;

class SmartCMView extends JFrame implements ActionListener  {

	private JButton refill, recover;
	private JTextField stateInfo;
	private JTextField numItems;
	private JTextField numSelfTests;
	private Controller controller;	
	
	public SmartCMView(){
		super(".:: Smart Coffee Machine ::.");
		setSize(600,120);

		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));

		JPanel infoLine = new JPanel();
		infoLine.setLayout(new BoxLayout(infoLine, BoxLayout.LINE_AXIS));
		stateInfo = new JTextField("--");
		stateInfo.setEditable(false);
		stateInfo.setPreferredSize(new Dimension(200,15));
		infoLine.add(new JLabel("State:"));
		infoLine.add(stateInfo);
		numItems = new JTextField("--");
		numItems.setEditable(false);
		numItems.setPreferredSize(new Dimension(200,15));
		infoLine.add(new JLabel("Num items:"));
		infoLine.add(numItems);
		numSelfTests = new JTextField("--");
		numSelfTests.setEditable(false);
		numSelfTests.setPreferredSize(new Dimension(200,15));
		infoLine.add(new JLabel("Num self-tests:"));
		infoLine.add(numSelfTests);
		mainPanel.add(infoLine);
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));

		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));	    
		refill = new JButton("Refill");
		refill.setEnabled(false);
		buttonPanel.add(refill);
		recover = new JButton("Recover");
		recover.setEnabled(false);
		buttonPanel.add(recover);
		refill.addActionListener(this);
		recover.addActionListener(this);
		mainPanel.add(buttonPanel);

		this.getContentPane().add(mainPanel);

		addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent ev){
				System.exit(-1);
			}
		});
	}

	public void registerController(Controller contr){
		this.controller = contr;
	}

	public void setState(String msg){
		SwingUtilities.invokeLater(() -> {
			stateInfo.setText(msg);
		});
	}
	
	public void setNumItems(String items){
		SwingUtilities.invokeLater(() -> {
			numItems.setText("" + items);
		});
	}

	public void setNumSelfTests(String msg){
		SwingUtilities.invokeLater(() -> {
			numSelfTests.setText("" + msg);
		});
	}
	
	public void startMaintenanceForRefilling() {
		SwingUtilities.invokeLater(() -> {
			refill.setEnabled(true);
		});
	}

	public void startMaintenanceForRecovering() {
		SwingUtilities.invokeLater(() -> {
			recover.setEnabled(true);
		});
	}
	
	public void actionPerformed(ActionEvent ev){
		  try {
			  if (ev.getActionCommand().equals("Refill")){
				  controller.notifyRefilled();
				  refill.setEnabled(false);
			  } else {
				  controller.notifyRecovered();
				  recover.setEnabled(false);
			  }
		  } catch (Exception ex){
			  ex.printStackTrace();
		  }
	  }
	
}
