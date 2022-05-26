package esiot.module_lab_4_2;

import esiot.module_lab_2_2.SerialCommChannel;

public class TestRemoteBlinkingBT {

	public static void main(String[] args) throws Exception {
		//SerialCommChannel channel = new SerialCommChannel(args[0],9600);		
		// SerialCommChannel channel = new SerialCommChannel("/dev/cu.isi00",9600);		
		SerialCommChannel channel = new SerialCommChannel("/dev/cu.DSDTECHHC-05",9600);		
		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		

		
		while (true){
			channel.sendMsg("1");
			String msg = channel.receiveMsg();
			System.out.println(msg);		
			Thread.sleep(500);
		
			channel.sendMsg("0");
			msg = channel.receiveMsg();
			System.out.println(msg);
			Thread.sleep(500);

		}
	}

}
