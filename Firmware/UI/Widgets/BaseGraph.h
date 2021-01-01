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
        // for(int i = 0; i < index; i++){
        //      painter->DrawPixel((uint16_t)(origin_x+i+1),(uint16_t)(origin_y + 179 - hist[i]),(uint16_t)Color565::Red);
        // }
        //   for(uint16_t i = 1; i < index; i++){
        //       for(uint16_t j = origin_y + 179 - hist[i];j <= origin_y + 179;j++)
        //          painter->DrawPixel(origin_x+i,j,(uint16_t)Color565::Red);
        //   }  
        

        // Drawing the Graph on Screen
        for(uint16_t i = 0; i < 250; i++){
                painter->DrawFillRectangle(origin_x+i+1,origin_y+180-hist[i],1,hist[i],(uint16_t)Color565::Red);
        }
}


};

#endif /* BASEGRAPH_H */