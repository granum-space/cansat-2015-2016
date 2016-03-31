/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.packet;

/**
 *
 * @author Kirs67
 */
public class DataPacket {
    final static int size = 30;
    final static int beacon = 0xFFFF;
    int number;
    int time, time_part;
    int temperature1, temperature2,
		pressure,
		humidity,
		O2, CO2,
		rezistance12, rezistance23, rezistance13;
    int legs, parachute;
    int cntrl;
    int truecntrl;
    @Override
    public String toString() {
        String str = new String();
        str+= "Data packet number";
        str+= Integer.toString(number);
        return str;
    }
    public boolean check() {
        truecntrl &= 0xffff;
        /*System.out.println(Integer.toHexString(cntrl));
        System.out.println(Integer.toHexString(truecntrl));*/
        return truecntrl==cntrl;
    }
}
