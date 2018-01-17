#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include "simple/server.hpp"
#include "simple_msgs/point.h"
#include "simple_msgs/quaternion.h"
#include "simple_msgs/pose.h"
#include "simple_msgs/bool.h"
#include "simple_msgs/string.h"
#include "simple_msgs/numeric_type.hpp"
#include "simple_msgs/rotation_matrix.h"
#include "simple_msgs/header.h"
#include "simple_msgs/point_stamped.h"
#include "simple_msgs/quaternion_stamped.h"
#include "simple_msgs/pose_stamped.h"
#include "simple_msgs/rotation_matrix_stamped.h"
#include "simple/client.hpp"
#include "simple_msgs/double.h"
#include "simple_msgs/float.h"
#include "simple_msgs/int.h"
#include <time.h>
#include <stdlib.h>
#include "test_utils.hpp"

// TEST FOR A CLIENT AND SERVER OF ALL DATA TYPES

SCENARIO("Client-Server to a Point message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server
    simple::Server<simple_msgs::Point> server("tcp://*:5555", callbackFunctionPoint);
    simple::Client<simple_msgs::Point> client("tcp://localhost:5555");

    WHEN("The client sends a request")
    {
      auto p = createRandomPoint();
      auto sentPoint = p;
      client.request(p);

      THEN("The data received is the equal to the sent point plus one's")
      {
        REQUIRE(p.getX() == Approx(sentPoint.getX() + 1.0));
        REQUIRE(p.getY() == Approx(sentPoint.getY() + 1.0));
        REQUIRE(p.getZ() == Approx(sentPoint.getZ() + 1.0));
      }
    }
  }
}

SCENARIO("Client-Server to a Pose message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server
    simple::Server<simple_msgs::Pose> server("tcp://*:5556", callbackFunctionPose);
    simple::Client<simple_msgs::Pose> client("tcp://localhost:5556");

    WHEN("The client sends a request")
    {
      auto p = createRandomPose();
      auto sentPose = p;
      client.request(p);
      THEN("The data received is the equal to the sent pose plus one's")
      {
        REQUIRE(p.getPosition().getX() == Approx(sentPose.getPosition().getX() + 1.0));
        REQUIRE(p.getPosition().getY() == Approx(sentPose.getPosition().getY() + 1.0));
        REQUIRE(p.getPosition().getZ() == Approx(sentPose.getPosition().getZ() + 1.0));
        REQUIRE(p.getQuaternion().getW() == Approx(sentPose.getQuaternion().getW() + 1.0));
        REQUIRE(p.getQuaternion().getX() == Approx(sentPose.getQuaternion().getX() + 1.0));
        REQUIRE(p.getQuaternion().getY() == Approx(sentPose.getQuaternion().getY() + 1.0));
        REQUIRE(p.getQuaternion().getZ() == Approx(sentPose.getQuaternion().getZ() + 1.0));
      }
    }
  }
}

SCENARIO("Client-Server to a Quaternion message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server
    simple::Client<simple_msgs::Quaternion> client("tcp://localhost:5557");
    simple::Server<simple_msgs::Quaternion> server("tcp://*:5557", callbackFunctionQuaternion);

    WHEN("The client sends a request")
    {
      auto q = createRandomQuaternion();
      auto sentQ = q;
      client.request(q);
      THEN("The data received is the equal to the sent pose plus one's")
      {
        REQUIRE(q.getW() == Approx(sentQ.getW() + 1.0));
        REQUIRE(q.getX() == Approx(sentQ.getX() + 1.0));
        REQUIRE(q.getY() == Approx(sentQ.getY() + 1.0));
        REQUIRE(q.getZ() == Approx(sentQ.getZ() + 1.0));
      }
    }
  }
}

SCENARIO("Client-Server to a Rotation Matrix message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server.
    simple::Client<simple_msgs::RotationMatrix> client("tcp://localhost:5558");
    simple::Server<simple_msgs::RotationMatrix> server("tcp://*:5558", callbackFunctionRotationMatrix);

    WHEN("The client sends a request")
    {
      auto r = createRandomRotationMatrix();
      client.request(r);
      THEN("The data received is the the identity matrix") { REQUIRE(r == simple_msgs::RotationMatrix()); }
    }
  }
}

SCENARIO("Client-Server to a String message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server
    simple::Client<simple_msgs::String> client("tcp://localhost:5559");
    simple::Server<simple_msgs::String> server("tcp://*:5559", callbackFunctionString);

    WHEN("The client sends a request")
    {
      auto p = createRandomString();
      client.request(p);

      THEN("The string received back is the default answer") { REQUIRE(p == "REPLY"); }
    }
  }
}

SCENARIO("Client-Server to a Bool message.")
{
  GIVEN("An instance of a server.")
  {
    // Start a server
    simple::Client<simple_msgs::Bool> client("tcp://localhost:5560");
    simple::Server<simple_msgs::Bool> server("tcp://*:5560", callbackFunctionBool);

    WHEN("The client sends a request")
    {
      auto p = createRandomBool();
      client.request(p);

      THEN("The data received is true") { REQUIRE(p == true); }
    }
  }
}
SCENARIO("Client-Server to a Double message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server
    simple::Client<simple_msgs::Double> client("tcp://localhost:5561");
    simple::Server<simple_msgs::Double> server("tcp://*:5561", callbackFunctionDouble);

    WHEN("The client sends a request")
    {
      auto p = createRandomDouble();
      auto sentDouble = p;
      client.request(p);
      THEN("The data received is the same as the one sent plus 1")
      {
        REQUIRE(p.get() == Approx(sentDouble.get() + 1.0));
      }
    }
  }
}

SCENARIO("Client-Server to a Int message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server
    simple::Client<simple_msgs::Int> client("tcp://localhost:5562");
    simple::Server<simple_msgs::Int> server("tcp://*:5562", callbackFunctionInt);

    WHEN("The client sends a request")
    {
      auto i = createRandomInt();
      auto sentInt = i;
      client.request(i);
      THEN("The data received is the same as the one sent plus 1") { REQUIRE(i == sentInt + 1); }
    }
  }
}

SCENARIO("Client-Server to a Float message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server
    simple::Client<simple_msgs::Float> client("tcp://localhost:5563");
    simple::Server<simple_msgs::Float> server("tcp://*:5563", callbackFunctionFloat);

    std::this_thread::sleep_for(std::chrono::seconds(5));
    WHEN("The client sends a request")
    {
      auto p = createRandomFloat();
      auto sentFloat = p;
      client.request(p);

      THEN("The data received is the same as the one sent plus 1")
      {
        REQUIRE(p.get() == Approx(sentFloat.get() + 1.0f));
      }
    }
  }
}

SCENARIO("Client-Server to a Header message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server
    simple::Client<simple_msgs::Header> client("tcp://localhost:5564");
    simple::Server<simple_msgs::Header> server("tcp://*:5564", callbackFunctionHeader);

    std::this_thread::sleep_for(std::chrono::seconds(5));
    WHEN("The client sends a request")
    {
      auto p = createRandomHeader();
      client.request(p);
      THEN("The data received is filled wth the standard values")
      {
        REQUIRE(p.getFrameID() == "ID");
        REQUIRE(p.getSequenceNumber() == 1);
        REQUIRE(p.getTimestamp() == 1.0);
      }
    }
  }
}

SCENARIO("Client-Server to a Stamped Point message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server
    simple::Server<simple_msgs::PointStamped> server("tcp://*:5565", callbackFunctionPointStamped);
    simple::Client<simple_msgs::PointStamped> client("tcp://localhost:5565");

    WHEN("The client sends a request")
    {
      auto p = createRandomPointStamped();
      auto sentPoint = p;
      client.request(p);
      simple_msgs::Point unitPoint(1, 1, 1);

      THEN("The data received is the equal to the sent point plus one's")
      {
        REQUIRE(p.getPoint().getX() == Approx(sentPoint.getPoint().getX() + 1.0));
        REQUIRE(p.getPoint().getY() == Approx(sentPoint.getPoint().getY() + 1.0));
        REQUIRE(p.getPoint().getZ() == Approx(sentPoint.getPoint().getZ() + 1.0));
        REQUIRE(p.getHeader().getFrameID() == "ID");
        REQUIRE(p.getHeader().getSequenceNumber() == 1);
        REQUIRE(p.getHeader().getTimestamp() == 1.0);
      }
    }
  }
}

SCENARIO("Client-Server to a Stamped Pose message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server
    simple::Server<simple_msgs::PoseStamped> server("tcp://*:5566", callbackFunctionPoseStamped);
    simple::Client<simple_msgs::PoseStamped> client("tcp://localhost:5566");

    WHEN("The client sends a request")
    {
      auto p = createRandomPoseStamped();
      auto sentPose = p;
      client.request(p);
      simple_msgs::Point unitPoint(1, 1, 1);
      THEN("The data received is the equal to the sent pose plus one's")
      {
        REQUIRE(p.getPose().getPosition().getX() == Approx(sentPose.getPose().getPosition().getX() + 1.0));
        REQUIRE(p.getPose().getPosition().getY() == Approx(sentPose.getPose().getPosition().getY() + 1.0));
        REQUIRE(p.getPose().getPosition().getZ() == Approx(sentPose.getPose().getPosition().getZ() + 1.0));
        REQUIRE(p.getPose().getQuaternion().getW() == Approx(sentPose.getPose().getQuaternion().getW() + 1.0));
        REQUIRE(p.getPose().getQuaternion().getX() == Approx(sentPose.getPose().getQuaternion().getX() + 1.0));
        REQUIRE(p.getPose().getQuaternion().getY() == Approx(sentPose.getPose().getQuaternion().getY() + 1.0));
        REQUIRE(p.getPose().getQuaternion().getZ() == Approx(sentPose.getPose().getQuaternion().getZ() + 1.0));
        REQUIRE(p.getHeader().getFrameID() == "ID");
        REQUIRE(p.getHeader().getSequenceNumber() == 1);
        REQUIRE(p.getHeader().getTimestamp() == 1.0);
      }
    }
  }
}

SCENARIO("Client-Server to a Stamped Quaternion message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server
    simple::Client<simple_msgs::QuaternionStamped> client("tcp://localhost:5567");
    simple::Server<simple_msgs::QuaternionStamped> server("tcp://*:5567", callbackFunctionQuaternionStamped);

    WHEN("The client sends a request")
    {
      auto q = createRandomQuaternionStamped();
      auto sentQ = q;
      client.request(q);
      THEN("The data received is the equal to the sent pose plus one's")
      {
        REQUIRE(q.getQuaternion().getW() == Approx(sentQ.getQuaternion().getW() + 1.0));
        REQUIRE(q.getQuaternion().getX() == Approx(sentQ.getQuaternion().getX() + 1.0));
        REQUIRE(q.getQuaternion().getY() == Approx(sentQ.getQuaternion().getY() + 1.0));
        REQUIRE(q.getQuaternion().getZ() == Approx(sentQ.getQuaternion().getZ() + 1.0));
        REQUIRE(q.getHeader().getFrameID() == "ID");
        REQUIRE(q.getHeader().getSequenceNumber() == 1);
        REQUIRE(q.getHeader().getTimestamp() == 1.0);
      }
    }
  }
}

SCENARIO("Client-Server to a Stamped Rotation Matrix message.")
{
  GIVEN("An instance of a server.")
  {
    // start a server.
    simple::Client<simple_msgs::RotationMatrixStamped> client("tcp://localhost:5568");
    simple::Server<simple_msgs::RotationMatrixStamped> server("tcp://*:5568", callbackFunctionRotationMatrixStamped);

    WHEN("The client sends a request")
    {
      auto r = createRandomRotationMatrixStamped();
      client.request(r);
      THEN("The data received is the the identity matrix")
      {
        REQUIRE(r.getRotationMatrix() == simple_msgs::RotationMatrix());
        REQUIRE(r.getHeader().getFrameID() == "ID");
        REQUIRE(r.getHeader().getSequenceNumber() == 1);
        REQUIRE(r.getHeader().getTimestamp() == 1.0);
      }
    }
  }
}
