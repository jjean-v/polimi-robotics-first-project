#include <chrono>
#include <cmath>
#include <memory>
#include <string>

// standard include
#include "rclcpp/rclcpp.hpp"

// custom tf message
#include "first_project/tf_error_msg/tf_error_msg.hpp"

// tf includes
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/exceptions.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"

// for easier writing, so we can write 500ms 
// instead of std::chrono::milliseconds(500)
using namespace std::chrono_literals;

class TfErrorNode : public rclcpp::Node
{
public:
	TfErrorNode()
	: Node("tf_error"),
		tf_buffer_(this->get_clock()),
		tf_listener_(tf_buffer_),
		start_time_(this->now())
	{
		base_link_frame_ = this->declare_parameter<std::string>("base_link_frame", "base_link");
		base_link2_frame_ = this->declare_parameter<std::string>("base_link2_frame", "base_link2");
		odom_frame_ = this->declare_parameter<std::string>("odom_frame", "odom");
		publish_rate_hz_ = this->declare_parameter<double>("publish_rate_hz", 20.0);

		pub_ = this->create_publisher<first_project::tf_error_msg::TfErrorMsg>(
            "/tf_error_msg",
             10);

		const auto period = std::chrono::duration<double>(1.0 / std::max(1.0, publish_rate_hz_));
		timer_ = this->create_wall_timer(
			std::chrono::duration_cast<std::chrono::nanoseconds>(period),
			std::bind(&TfErrorNode::on_timer, this));
	}

private:
	void on_timer()
	{
		first_project::tf_error_msg::TfErrorMsg msg;
		msg.header.stamp = this->now();
		msg.header.frame_id = base_link_frame_;

		// 1) Distance between base_link and base_link2 (or configured frames)
		try {
			const auto tf_err = tf_buffer_.lookupTransform(
				base_link_frame_, base_link2_frame_, tf2::TimePointZero);

			const auto & t = tf_err.transform.translation;
			msg.tf_error = static_cast<float>(std::sqrt(t.x * t.x + t.y * t.y)); // we ignore z for simplicity
		} catch (const tf2::TransformException & ex) {
			RCLCPP_WARN_THROTTLE(
				this->get_logger(), *this->get_clock(), 2000,
				"TF error lookup failed (%s <- %s): %s",
				base_link_frame_.c_str(), base_link2_frame_.c_str(), ex.what());
			msg.tf_error = 0.0f;
		}

		// 2b) travelled distance in meters (integrated in travel_ref_frame)
		try {
			const auto tf_travel = tf_buffer_.lookupTransform(
				odom_frame_, base_link2_frame_, tf2::TimePointZero);

			const auto & t = tf_travel.transform.translation;
			if (has_prev_pos_) {
				const double dx = t.x - prev_x_;
				const double dy = t.y - prev_y_;
				// const double dz = t.z - prev_z_;
				travelled_distance_ += std::sqrt(dx * dx + dy * dy); // we ignore dz for simplicity
			}

			prev_x_ = t.x;
			prev_y_ = t.y;
			// prev_z_ = t.z;
			has_prev_pos_ = true;
		} catch (const tf2::TransformException & ex) {
			RCLCPP_WARN_THROTTLE(
				this->get_logger(), *this->get_clock(), 2000,
				"Travel TF lookup failed (%s <- %s): %s",
				odom_frame_.c_str(), base_link2_frame_.c_str(), ex.what());
		}

		msg.travelled_distance = static_cast<float>(travelled_distance_);

		const auto elapsed = this->now() - start_time_;
		msg.time_from_start = static_cast<int32_t>(elapsed.seconds());

		pub_->publish(msg);
	}

  	std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  	std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

	rclcpp::Publisher<first_project::tf_error_msg::TfErrorMsg>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;

	rclcpp::Time start_time_;
	std::string base_link_frame_;
	std::string base_link2_frame_;
	std::string odom_frame_;
	double publish_rate_hz_ {20.0};

	bool has_prev_pos_ {false};
	double prev_x_ {0.0};
	double prev_y_ {0.0};
	// double prev_z_ {0.0};
	double travelled_distance_ {0.0};
};

int main(int argc, char ** argv)
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<TfErrorNode>());
	rclcpp::shutdown();
	return 0;
}

