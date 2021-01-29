#ifndef _ROS_open_base_Movement_h
#define _ROS_open_base_Movement_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "open_base/Velocity.h"
#include "open_base/MovementGeneric.h"
#include "open_base/MovementBezier.h"

namespace open_base
{

  class Movement : public ros::Msg
  {
    public:
      typedef uint8_t _movement_type;
      _movement_type movement;
      typedef open_base::Velocity _wheel_type;
      _wheel_type wheel;
      typedef open_base::MovementGeneric _generic_type;
      _generic_type generic;
      typedef open_base::MovementBezier _bezier_type;
      _bezier_type bezier;
      enum { BEZIER = 0 };
      enum { GENERIC = 1 };
      enum { NONE = 2 };
      enum { WHEEL = 3 };
      enum { POSITION_ABSOLUTE = 0 };
      enum { POSITION_RELATIVE = 1 };
      enum { VELOCITY = 2 };
      enum { HYBRID = 0 };
      enum { MOBILE = 1 };
      enum { MOBILE_RAW = 2 };
      enum { WORLD = 3 };

    Movement():
      movement(0),
      wheel(),
      generic(),
      bezier()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->movement >> (8 * 0)) & 0xFF;
      offset += sizeof(this->movement);
      offset += this->wheel.serialize(outbuffer + offset);
      offset += this->generic.serialize(outbuffer + offset);
      offset += this->bezier.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->movement =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->movement);
      offset += this->wheel.deserialize(inbuffer + offset);
      offset += this->generic.deserialize(inbuffer + offset);
      offset += this->bezier.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "open_base/Movement"; };
    const char * getMD5(){ return "68a9ba8e542ff32c2d272bc9497c5912"; };

  };

}
#endif
