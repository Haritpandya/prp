/*
 *    Copyright (C) 2015 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
       \brief
       @author authorname
*/




#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H

#include <genericworker.h>
#include <innermodel/innermodel.h>

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <agmInner/agmInner.h>
#include <boost/filesystem.hpp>
#include <sstream>

#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#ifdef __cplusplus
extern "C"{
#endif 
    
#include "ccv/ccv.h"

#ifdef __cplusplus
}

#endif

//#include "t.hpp"

class SpecificWorker : public GenericWorker
{
Q_OBJECT
private:
	ccv_convnet_t* convnet;
	fstream file;
	bool first;

public:
	SpecificWorker(MapPrx& mprx);	
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);

	bool reloadConfigAgent();
	bool activateAgent(const ParameterMap &prs);
	bool setAgentParameters(const ParameterMap &prs);
	ParameterMap getAgentParameters();
	void killAgent();
	int uptimeAgent();
	bool deactivateAgent();
	StateStruct getAgentState();
        
	void processDataFromDir(const boost::filesystem::path &base_dir);
	//given an image and its location it process its objects and save them to the corresponding location
	void processImage(const ColorSeq &image, std::string location);
	void save_tables_info();
	void read_tables_info();
        
	void getLabelsFromImage(const ColorSeq &image, ResultList &result);
	void structuralChange(const RoboCompAGMWorldModel::Event &modification);
	void edgesUpdated(const RoboCompAGMWorldModel::EdgeSequence &modifications);
	void edgeUpdated(const RoboCompAGMWorldModel::Edge &modification);
	void symbolUpdated(const RoboCompAGMWorldModel::Node &modification);

public slots:
	void compute(); 	

private:
	std::map<std::string, double>  table1;
	std::map<std::string, double>  table2;
	std::map<std::string, double>  table3;
	std::map<std::string, double>  table4;
		
	std::string action;
	ParameterMap params;
	AGMModel::SPtr worldModel;
	InnerModel *innerModel;
	bool active;
	bool setParametersAndPossibleActivation(const ParameterMap &prs, bool &reactivated);
	void sendModificationProposal(AGMModel::SPtr &worldModel, AGMModel::SPtr &newModel);

	
	void action_imagineMostLikelyMugInPosition();
};

#endif

