/******************************************************************************
   STDR Simulator - Simple Two DImensional Robot Simulator
   Copyright (C) 2013 STDR Simulator
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
   
   Authors : 
   * Manos Tsardoulias, etsardou@gmail.com
   * Aris Thallas, aris.thallas@gmail.com
   * Chris Zalidis, zalidis@gmail.com 
******************************************************************************/

#include "stdr_gui/stdr_gui_sensors/stdr_gui_robot.h"

namespace stdr_gui{

	CGuiRobot::CGuiRobot(const stdr_msgs::RobotIndexedMsg& msg)
	{
		robot_initialized_=false;
		initial_pose_=msg.robot.initialPose;
		current_pose_=initial_pose_;
		footprint_=msg.robot.footprint;
		radius_=msg.robot.footprint.radius;
		frame_id_=msg.name;
		show_label_=true;
		show_circles_=false;
		for(unsigned int i=0;i<msg.robot.laserSensors.size();i++){
			CGuiLaser *l=new CGuiLaser(msg.robot.laserSensors[i],frame_id_);
			lasers_.push_back(l);
		}
		robot_initialized_=true;
	}

	void CGuiRobot::draw(QImage *m,float ocgd,tf::TransformListener *listener)
	{
		if(!robot_initialized_) 
			return;
		resolution_=ocgd;
		tf::StampedTransform transform;
		
		try{
			listener->lookupTransform("map", 
				frame_id_.c_str(),ros::Time(0), transform);
		}
		catch (tf::TransformException ex){
			ROS_DEBUG("%s",ex.what());
		}
		tfScalar roll,pitch,yaw;
		current_pose_.x=transform.getOrigin().x();
		current_pose_.y=transform.getOrigin().y();
		transform.getBasis().getRPY(roll,pitch,yaw);
		current_pose_.theta=yaw;
		drawSelf(m);
		for(unsigned int i=0;i<lasers_.size();i++){
			lasers_[i]->paint(m,resolution_,current_pose_);
		}
	}
	
	void CGuiRobot::drawSelf(QImage *m)
	{
		QPainter painter(m);
		painter.setPen(Qt::blue);
		
		painter.drawEllipse(
			(current_pose_.x-radius_/2)/resolution_,
			(current_pose_.y-radius_/2)/resolution_,
			radius_/resolution_,
			radius_/resolution_);
			
		painter.drawLine(	
			current_pose_.x/resolution_,
			current_pose_.y/resolution_,
			current_pose_.x/resolution_+
				radius_/resolution_*1.05*cos(current_pose_.theta),
			current_pose_.y/resolution_+
				radius_/resolution_*1.05*sin(current_pose_.theta));
		
		if(show_circles_){
			painter.setPen(QColor(255,0,0,150));
			for(unsigned int i=0;i<5;i++){
				painter.drawEllipse(
					(current_pose_.x-(i+1.0)/2.0)/resolution_,
					(current_pose_.y-(i+1.0)/2.0)/resolution_,
					(i+1.0)/resolution_,
					(i+1.0)/resolution_);
			}
		}
	}
	
	bool CGuiRobot::checkEventProximity(QPoint p)
	{
		float dx=p.x()*resolution_-current_pose_.x;
		float dy=p.y()*resolution_-current_pose_.y;
		float dist=sqrt(pow(dx,2)+pow(dy,2));
		return dist<=radius_;
	}
	
	CGuiRobot::~CGuiRobot(void)
	{
		
	}
	
	std::string CGuiRobot::getFrameId(void){
		return frame_id_;
	}
	
	void CGuiRobot::drawLabel(QImage *m,float ocgd){
		QPainter painter(m);
		
		painter.setPen(Qt::black);
		
		painter.drawRect(
			current_pose_.x/ocgd+10,
			m->height()-(current_pose_.y/ocgd)-30,
			100,
			20);
			
		painter.setPen(Qt::white);
		
		painter.fillRect(
			current_pose_.x/ocgd+10,
			m->height()-(current_pose_.y/ocgd)-30,
			100,
			20,
			QBrush(QColor(0,0,0,140)));
		
		painter.drawText(
			current_pose_.x/ocgd+12,
			m->height()-(current_pose_.y/ocgd)-15,
			QString(frame_id_.c_str()));
	}
	
	void CGuiRobot::setShowLabel(bool b)
	{
		show_label_=b;
	}
	
	bool CGuiRobot::getShowLabel(void){
		return show_label_;
	}
	
	void CGuiRobot::toggleShowLabel(void){
		show_label_=!show_label_;
	}
	
	void CGuiRobot::toggleShowCircles(void){
		show_circles_=!show_circles_;
	}
	
	QPoint CGuiRobot::getCurrentPose(void){
		return QPoint(current_pose_.x/resolution_,current_pose_.y/resolution_);
	}
}
