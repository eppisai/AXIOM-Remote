#ifndef BASEGRAPH_H
#define BASEGRAPH_H

#include "../Painter/Painter.h"
#include "../Color565.h"
# define my_sizeof(type) ((char *)(&type+1)-(char*)(&type)) 
class IPainter;

class BaseGraph
{  
  uint8_t *data;
  int origin_x = 20,origin_y = 40;
  public:
   BaseGraph(uint8_t graph_data[]) : data(graph_data){}
   
   void Draw(IPainter* painter)
   {
    Drawcartesianplane(painter,origin_x,origin_y);
    DrawBaseData(data,painter,origin_x,origin_y);
   }
    
    // Drawing cartesian plane
    void Drawcartesianplane(IPainter* painter,int origin_x,int origin_y){
      painter->DrawFastVLine(origin_x, origin_y, 180, (uint16_t)Color565::Black);
      painter->DrawFastHLine(origin_x, origin_y + 180, origin_x + 250, (uint16_t)Color565::Black);
    }

    void DrawBaseData(uint8_t data[],IPainter* painter,int origin_x,int origin_y){
        // x axis is of 250 pixel, and y axis is of 180 pixel
        int x_width = 250,y_width = 180,index = 0;
        
        //size of original histogram
        int size = my_sizeof(data)/my_sizeof(data[0]);
        
        //since the size of x axis of the original histogram can be greater than 250 pixel,so we compress its coordinates to 250 pixel.
        //interval is how much 1 unit of our histogram will represent the original histogram
        int interval = (size > x_width) ? size/x_width : 1;
        interval = (size%x_width > 0) ? interval + 1 : interval;

        //hist will store the new histogram to be drawn in firmware.
        int hist[251] = {0},high_y = 0,avg;
        for(int i  = 0; i < size; i+=interval){
            avg = 0;
            for(int j = i; j < size && j <= i + interval; j++) avg += (int)data[j];
            avg = (i+interval < x_width) ? (avg/interval) : (avg/(size%x_width));
            hist[index++] = avg;
            //high_y stores the maxima of y coordinate in original histogram
            high_y = (avg>high_y) ? avg : high_y;
        }

        //since the max y co-ordinate of original graph can be grater than 180 pixel, so we compress it to 180. 
        if(high_y > y_width){
        interval = high_y/y_width;
            interval = (high_y%y_width > 0) ? interval + 1 : interval;
        for(int i  = 0; i < interval; i++){
            hist[i] =  (hist[i]/interval);
        }
        }
        // Drawing the Graph on Screen : method 1
        // for(int i = 0; i < index; i++){
        //      painter->DrawPixel((uint16_t)(origin_x+i+1),(uint16_t)(origin_y + 179 - hist[i]),(uint16_t)Color565::Red);
        // }
        // Drawing the Graph on Screen : method 2
        // for(uint16_t i = 1; i < index; i++){
        //       for(uint16_t j = origin_y + 179 - hist[i];j <= origin_y + 179;j++)
        //          painter->DrawPixel(origin_x+i,j,(uint16_t)Color565::Red);
        //   }  
        

        // Drawing the Graph on Screen : method 3
        // for(uint16_t i = 0; i < 250; i++){
        //         painter->DrawFillRectangle(origin_x+i+1,origin_y+180-hist[i],1,hist[i],(uint16_t)Color565::Red);
        // }

        painter->DrawFillRectangle(21,139,1,81,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(22,141,1,79,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(23,142,1,78,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(24,172,1,48,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(25,172,1,48,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(26,172,1,48,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(27,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(28,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(29,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(30,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(31,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(32,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(33,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(34,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(35,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(36,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(37,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(38,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(39,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(40,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(41,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(42,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(43,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(44,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(45,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(46,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(47,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(48,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(49,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(50,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(51,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(52,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(53,169,1,51,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(54,193,1,27,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(55,70,1,150,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(56,126,1,94,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(57,139,1,81,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(58,141,1,79,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(59,142,1,78,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(60,172,1,48,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(61,172,1,48,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(62,172,1,48,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(63,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(64,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(65,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(66,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(67,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(68,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(69,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(70,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(71,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(72,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(73,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(74,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(75,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(76,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(77,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(78,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(79,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(80,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(81,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(82,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(83,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(84,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(85,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(86,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(87,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(88,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(89,169,1,51,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(90,193,1,27,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(91,70,1,150,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(92,140,1,80,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(93,172,1,48,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(94,172,1,48,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(95,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(96,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(97,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(98,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(99,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(100,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(101,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(102,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(103,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(104,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(105,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(106,125,1,95,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(107,142,1,78,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(108,172,1,48,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(109,172,1,48,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(110,172,1,48,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(111,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(112,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(113,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(114,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(115,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(116,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(117,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(118,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(119,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(120,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(121,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(122,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(123,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(124,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(125,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(126,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(127,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(128,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(129,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(130,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(131,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(132,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(133,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(134,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(135,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(136,188,1,32,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(137,169,1,51,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(138,193,1,27,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(139,70,1,150,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(140,126,1,94,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(141,139,1,81,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(142,141,1,79,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(143,142,1,78,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(144,172,1,48,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(145,219,1,1,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(146,219,1,1,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(147,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(148,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(149,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(150,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(151,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(152,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(153,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(154,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(155,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(156,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(157,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(158,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(159,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(160,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(161,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(162,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(163,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(164,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(165,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(166,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(167,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(168,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(169,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(170,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(171,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(172,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(173,219,1,1,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(174,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(175,217,1,3,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(176,219,1,1,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(177,219,1,1,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(178,219,1,1,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(179,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(180,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(181,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(182,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(183,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(184,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(185,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(186,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(187,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(188,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(189,220,1,0,(uint16_t)Color565::Red);
        painter->DrawFillRectangle(190,220,1,0,(uint16_t)Color565::Red);




                
}
};

#endif /* BASEGRAPH_H */
