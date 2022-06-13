package esiot.smart_cm;

import javax.swing.SwingUtilities;

class SmartCMConsole   {

	static SmartCMView view = null;
	static LogView log = null;

	public static void main(String[] args) throws Exception {	
		/*
		if (args.length != 1){
			System.err.println("Args: <serial port>");
			System.exit(1);
		}*/
		SwingUtilities.invokeAndWait(() -> {
			view = new SmartCMView();
			log = new LogView();
		});
		String portName = "/dev/cu.usbmodem1442401";
		Controller contr = new Controller(portName,view,log);
		view.registerController(contr);
		SwingUtilities.invokeLater(() -> {
			view.setVisible(true);
			log.setVisible(true);
		});
	}
}