package esiot.module_lab_4_2;

import esiot.module_lab_2_2.CommChannel;
import esiot.module_lab_2_2.SerialCommChannel;

public class TestPingPongBT {

	public static void main(String[] args) throws Exception {
		// CommChannel channel = new SerialCommChannel(args[0],9600);	
		// CommChannel channel = new SerialCommChannel("/dev/cu.isi00-DevB",9600);	
		// CommChannel channel = new ExtendedSerialCommChannel("/dev/cu.usbmodem14201",9600);	
		// CommChannel channel = new ExtendedSerialCommChannel("/dev/cu.isi00-DevB",9600);	
		CommChannel channel = new ExtendedSerialCommChannel("/dev/cu.DSDTECHHC-05",9600);	

		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		

		
		while (true){
			System.out.println("Sending ping");
			channel.sendMsg("ping");
			String msg = channel.receiveMsg();
			System.out.println("Received: "+msg);		
			Thread.sleep(500);
		}
	}

}
