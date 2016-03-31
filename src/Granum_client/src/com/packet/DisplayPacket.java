/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.packet;

import com.packet.PacketParser.PacketAcceptor;

/**
 *
 * @author Kirs67
 */
public class DisplayPacket implements PacketAcceptor {
    
    public DataPacket datapacket = new DataPacket();
    public AccPacket accpacket = new AccPacket();
    @Override
    public void onDataPacket(DataPacket packet) {
        datapacket = packet;
    }
    @Override
    public void onAccPacket(AccPacket packet) {
        accpacket = packet;
    }
}
