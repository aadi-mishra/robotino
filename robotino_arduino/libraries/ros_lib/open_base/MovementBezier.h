#ifndef _ROS_open_base_MovementBezier_h
#define _ROS_open_base_MovementBezier_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"

namespace open_base
{

  class MovementBezier : public ros::Msg
  {
    public:
      typedef uint8_t _frame_type;
      _frame_type frame;
      uint32_t targetTranslation_length;
      typedef geometry_msgs::Pose2D _targetTranslation_type;
      _targetTranslation_type st_targetTranslation;
      _targetTranslation_type * targetTranslation;
      uint32_t targetRotation_length;
      typedef float _targetRotation_type;
      _targetRotation_type st_targetRotation;
      _targetRotation_type * targetRotation;
      typedef float _step_type;
      _step_type step;
      typedef bool _offsetTraslation_type;
      _offsetTraslation_type offsetTraslation;
      typedef bool _offsetRotation_type;
      _offsetRotation_type offsetRotation;

    MovementBezier():
      frame(0),
      targetTranslation_length(0), targetTranslation(NULL),
      targetRotation_length(0), targetRotation(NULL),
      step(0),
      offsetTraslation(0),
      offsetRotation(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->frame >> (8 * 0)) & 0xFF;
      offset += sizeof(this->frame);
      *(outbuffer + offset + 0) = (this->targetTranslation_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->targetTranslation_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->targetTranslation_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->targetTranslation_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->targetTranslation_length);
      for( uint32_t i = 0; i < targetTranslation_length; i++){
      offset += this->targetTranslation[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->targetRotation_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->targetRotation_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->targetRotation_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->targetRotation_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->targetRotation_length);
      for( uint32_t i = 0; i < targetRotation_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->targetRotation[i]);
      }
      offset += serializeAvrFloat64(outbuffer + offset, this->step);
      union {
        bool real;
        uint8_t base;
      } u_offsetTraslation;
      u_offsetTraslation.real = this->offsetTraslation;
      *(outbuffer + offset + 0) = (u_offsetTraslation.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->offsetTraslation);
      union {
        bool real;
        uint8_t base;
      } u_offsetRotation;
      u_offsetRotation.real = this->offsetRotation;
      *(outbuffer + offset + 0) = (u_offsetRotation.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->offsetRotation);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->frame =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->frame);
      uint32_t targetTranslation_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      targetTranslation_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      targetTranslation_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      targetTranslation_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->targetTranslation_length);
      if(targetTranslation_lengthT > targetTranslation_length)
        this->targetTranslation = (geometry_msgs::Pose2D*)realloc(this->targetTranslation, targetTranslation_lengthT * sizeof(geometry_msgs::Pose2D));
      targetTranslation_length = targetTranslation_lengthT;
      for( uint32_t i = 0; i < targetTranslation_length; i++){
      offset += this->st_targetTranslation.deserialize(inbuffer + offset);
        memcpy( &(this->targetTranslation[i]), &(this->st_targetTranslation), sizeof(geometry_msgs::Pose2D));
      }
      uint32_t targetRotation_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      targetRotation_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      targetRotation_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      targetRotation_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->targetRotation_length);
      if(targetRotation_lengthT > targetRotation_length)
        this->targetRotation = (float*)realloc(this->targetRotation, targetRotation_lengthT * sizeof(float));
      targetRotation_length = targetRotation_lengthT;
      for( uint32_t i = 0; i < targetRotation_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_targetRotation));
        memcpy( &(this->targetRotation[i]), &(this->st_targetRotation), sizeof(float));
      }
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->step));
      union {
        bool real;
        uint8_t base;
      } u_offsetTraslation;
      u_offsetTraslation.base = 0;
      u_offsetTraslation.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->offsetTraslation = u_offsetTraslation.real;
      offset += sizeof(this->offsetTraslation);
      union {
        bool real;
        uint8_t base;
      } u_offsetRotation;
      u_offsetRotation.base = 0;
      u_offsetRotation.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->offsetRotation = u_offsetRotation.real;
      offset += sizeof(this->offsetRotation);
     return offset;
    }

    const char * getType(){ return "open_base/MovementBezier"; };
    const char * getMD5(){ return "ded95d34881d8c480a26fcec4fc049df"; };

  };

}
#endif
