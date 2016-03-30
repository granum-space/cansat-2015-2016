/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.packet;

import java.util.ArrayList;
import java.util.Collections;

/**
 *
 * @author Kirs67, Vasiliy.Prokopiev
 */
public class PacketParser {
    // Состояние объекта
    private enum State
    {
        STATE_IN_SEARCH, // Состояние поиска макера начала пакета
        STATE_FOUND_FF, //Состояние после нахождение первой части маркера
        STATE_IN_ACCUMULATION // Состояние накопления данных пакета
    };
    
    // Интерфейс 
    public interface PacketAcceptor
    {
        void onDataPacket(DataPacket packet);
        void onAccPacket(AccPacket packet);
    }
    
    
    State _state = State.STATE_IN_SEARCH;
    private ArrayList<Byte> _dataContainer;
    private PacketAcceptor _acceptor = null;

    
    public void addBytes(Byte[] bytes)
    {
        Collections.addAll(_dataContainer, bytes);
        for (Byte byte1 : bytes) {
            switch (_state) {
                case STATE_IN_SEARCH:
                    if (byte1 == 0xff) {
                        _state = State.STATE_FOUND_FF;
                        _dataContainer.add(byte1);
                    }
                    break;
                case STATE_FOUND_FF:
                    if (byte1 == 0xff) {
                        _state=State.STATE_IN_ACCUMULATION;
                        _dataContainer.add(byte1);
                    }
                    else {
                        _state = State.STATE_IN_SEARCH;
                        _dataContainer.clear();
                    }
                case STATE_IN_ACCUMULATION:
                    if(_dataContainer.size()== DataPacket.size) {
                        if(check(_dataContainer)) {
                            
                        }
                        else {
                            _dataContainer.clear();
                            _state = State.STATE_IN_SEARCH;
                        }
                    }
                    else {
                        _dataContainer.add(byte1);
                    }
            }
        }
    }


    static private boolean check(ArrayList<Byte> data)
    {
        int retval = 0;
        for (int i = 0; i < DataPacket.size-2;i++)
        {
            retval += (int)data.get(i) & 0xFF;
        }
        retval &= 0xFFFF;
        int cntrl = (int)(data.get(29)<<8 | data.get(28));
        return retval == cntrl;
    }
    
    // функции разбора пакетов. Переименовать на нужные
    // и заменить классы на правильные
    private void onDataPacketFound(ArrayList<Byte> data)
    {
        DataPacket packet = new DataPacket();
        packet.number = (int)((data.get(3)<<8)| data.get(2));
        packet.time = (int)(data.get(5)<<8 | data.get(4));
        packet.time_part = (int)(data.get(7)<<8 | data.get(6));
        packet.temperature1 = (int)(data.get(9)<<8 | data.get(8));
        packet.temperature2 = (int)(data.get(11)<<8 | data.get(10));
        packet.pressure = (int)(data.get(13)<<8 | data.get(12));
        packet.humidity = (int)(data.get(15)<<8 | data.get(14));
        packet.O2 = (int)(data.get(17)<<8 | data.get(16));
        packet.CO2 = (int)(data.get(19)<<8 | data.get(18));
        packet.rezistance12 = (int)(data.get(21)<<8 | data.get(20));
        packet.rezistance23 = (int)(data.get(23)<<8 | data.get(22));
        packet.rezistance13 = (int)(data.get(25)<<8 | data.get(24));
        packet.legs = data.get(26);
        packet.parachute = data.get(27);
        packet.cntrl = (int)(data.get(29)<<8 | data.get(28));
        if (_acceptor != null)
        {
            _acceptor.onDataPacket(packet);
        }
    }
    

    private void onAccPacketFound(Byte[] data)
    {
        AccPacket packet = new AccPacket();
        // разбираем байты на пакет
         
        // и передаем наблюдателю 
        if (_acceptor != null)
        {
            _acceptor.onAccPacket(packet);
        }
    }

    
    void setAcceptor(PacketAcceptor acceptor)
    {
        _acceptor = acceptor;
    }
}
