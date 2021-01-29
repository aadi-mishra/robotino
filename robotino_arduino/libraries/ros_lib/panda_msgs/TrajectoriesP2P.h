#ifndef _ROS_SERVICE_TrajectoriesP2P_h
#define _ROS_SERVICE_TrajectoriesP2P_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace panda_msgs
{

static const char TRAJECTORIESP2P[] = "panda_msgs/TrajectoriesP2P";

  class TrajectoriesP2PRequest : public ros::Msg
  {
    public:
      uint32_t source_length;
      typedef float _source_type;
      _source_type st_source;
      _source_type * source;
      uint32_t target_length;
      typedef float _target_type;
      _target_type st_target;
      _target_type * target;

    TrajectoriesP2PRequest():
      source_length(0), source(NULL),
      target_length(0), target(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->source_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->source_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->source_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->source_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->source_length);
      for( uint32_t i = 0; i < source_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->source[i]);
      }
      *(outbuffer + offset + 0) = (this->target_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->target_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->target_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->target_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->target_length);
      for( uint32_t i = 0; i < target_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->target[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t source_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      source_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      source_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      source_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->source_length);
      if(source_lengthT > source_length)
        this->source = (float*)realloc(this->source, source_lengthT * sizeof(float));
      source_length = source_lengthT;
      for( uint32_t i = 0; i < source_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_source));
        memcpy( &(this->source[i]), &(this->st_source), sizeof(float));
      }
      uint32_t target_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      target_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      target_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      target_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->target_length);
      if(target_lengthT > target_length)
        this->target = (float*)realloc(this->target, target_lengthT * sizeof(float));
      target_length = target_lengthT;
      for( uint32_t i = 0; i < target_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_target));
        memcpy( &(this->target[i]), &(this->st_target), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return TRAJECTORIESP2P; };
    const char * getMD5(){ return "2a2d08a32fbc04976e12450c4c1412e2"; };

  };

  class TrajectoriesP2PResponse : public ros::Msg
  {
    public:
      uint32_t theta1_length;
      typedef float _theta1_type;
      _theta1_type st_theta1;
      _theta1_type * theta1;
      uint32_t theta2_length;
      typedef float _theta2_type;
      _theta2_type st_theta2;
      _theta2_type * theta2;
      uint32_t theta3_length;
      typedef float _theta3_type;
      _theta3_type st_theta3;
      _theta3_type * theta3;
      uint32_t theta4_length;
      typedef float _theta4_type;
      _theta4_type st_theta4;
      _theta4_type * theta4;
      uint32_t theta5_length;
      typedef float _theta5_type;
      _theta5_type st_theta5;
      _theta5_type * theta5;
      uint32_t theta6_length;
      typedef float _theta6_type;
      _theta6_type st_theta6;
      _theta6_type * theta6;
      uint32_t theta7_length;
      typedef float _theta7_type;
      _theta7_type st_theta7;
      _theta7_type * theta7;

    TrajectoriesP2PResponse():
      theta1_length(0), theta1(NULL),
      theta2_length(0), theta2(NULL),
      theta3_length(0), theta3(NULL),
      theta4_length(0), theta4(NULL),
      theta5_length(0), theta5(NULL),
      theta6_length(0), theta6(NULL),
      theta7_length(0), theta7(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->theta1_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->theta1_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->theta1_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->theta1_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->theta1_length);
      for( uint32_t i = 0; i < theta1_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->theta1[i]);
      }
      *(outbuffer + offset + 0) = (this->theta2_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->theta2_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->theta2_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->theta2_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->theta2_length);
      for( uint32_t i = 0; i < theta2_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->theta2[i]);
      }
      *(outbuffer + offset + 0) = (this->theta3_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->theta3_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->theta3_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->theta3_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->theta3_length);
      for( uint32_t i = 0; i < theta3_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->theta3[i]);
      }
      *(outbuffer + offset + 0) = (this->theta4_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->theta4_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->theta4_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->theta4_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->theta4_length);
      for( uint32_t i = 0; i < theta4_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->theta4[i]);
      }
      *(outbuffer + offset + 0) = (this->theta5_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->theta5_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->theta5_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->theta5_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->theta5_length);
      for( uint32_t i = 0; i < theta5_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->theta5[i]);
      }
      *(outbuffer + offset + 0) = (this->theta6_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->theta6_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->theta6_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->theta6_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->theta6_length);
      for( uint32_t i = 0; i < theta6_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->theta6[i]);
      }
      *(outbuffer + offset + 0) = (this->theta7_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->theta7_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->theta7_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->theta7_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->theta7_length);
      for( uint32_t i = 0; i < theta7_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->theta7[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t theta1_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      theta1_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      theta1_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      theta1_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->theta1_length);
      if(theta1_lengthT > theta1_length)
        this->theta1 = (float*)realloc(this->theta1, theta1_lengthT * sizeof(float));
      theta1_length = theta1_lengthT;
      for( uint32_t i = 0; i < theta1_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_theta1));
        memcpy( &(this->theta1[i]), &(this->st_theta1), sizeof(float));
      }
      uint32_t theta2_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      theta2_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      theta2_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      theta2_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->theta2_length);
      if(theta2_lengthT > theta2_length)
        this->theta2 = (float*)realloc(this->theta2, theta2_lengthT * sizeof(float));
      theta2_length = theta2_lengthT;
      for( uint32_t i = 0; i < theta2_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_theta2));
        memcpy( &(this->theta2[i]), &(this->st_theta2), sizeof(float));
      }
      uint32_t theta3_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      theta3_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      theta3_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      theta3_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->theta3_length);
      if(theta3_lengthT > theta3_length)
        this->theta3 = (float*)realloc(this->theta3, theta3_lengthT * sizeof(float));
      theta3_length = theta3_lengthT;
      for( uint32_t i = 0; i < theta3_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_theta3));
        memcpy( &(this->theta3[i]), &(this->st_theta3), sizeof(float));
      }
      uint32_t theta4_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      theta4_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      theta4_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      theta4_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->theta4_length);
      if(theta4_lengthT > theta4_length)
        this->theta4 = (float*)realloc(this->theta4, theta4_lengthT * sizeof(float));
      theta4_length = theta4_lengthT;
      for( uint32_t i = 0; i < theta4_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_theta4));
        memcpy( &(this->theta4[i]), &(this->st_theta4), sizeof(float));
      }
      uint32_t theta5_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      theta5_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      theta5_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      theta5_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->theta5_length);
      if(theta5_lengthT > theta5_length)
        this->theta5 = (float*)realloc(this->theta5, theta5_lengthT * sizeof(float));
      theta5_length = theta5_lengthT;
      for( uint32_t i = 0; i < theta5_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_theta5));
        memcpy( &(this->theta5[i]), &(this->st_theta5), sizeof(float));
      }
      uint32_t theta6_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      theta6_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      theta6_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      theta6_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->theta6_length);
      if(theta6_lengthT > theta6_length)
        this->theta6 = (float*)realloc(this->theta6, theta6_lengthT * sizeof(float));
      theta6_length = theta6_lengthT;
      for( uint32_t i = 0; i < theta6_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_theta6));
        memcpy( &(this->theta6[i]), &(this->st_theta6), sizeof(float));
      }
      uint32_t theta7_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      theta7_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      theta7_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      theta7_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->theta7_length);
      if(theta7_lengthT > theta7_length)
        this->theta7 = (float*)realloc(this->theta7, theta7_lengthT * sizeof(float));
      theta7_length = theta7_lengthT;
      for( uint32_t i = 0; i < theta7_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_theta7));
        memcpy( &(this->theta7[i]), &(this->st_theta7), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return TRAJECTORIESP2P; };
    const char * getMD5(){ return "52e648d1fc2b6862e3c3627db673046e"; };

  };

  class TrajectoriesP2P {
    public:
    typedef TrajectoriesP2PRequest Request;
    typedef TrajectoriesP2PResponse Response;
  };

}
#endif
