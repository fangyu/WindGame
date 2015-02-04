//
//  StlHeader.h
//  FirstGame
//
//  Created by Yan Pei on 13-10-9.
//
//

#ifndef FirstGame_StlHeader_h
#define FirstGame_StlHeader_h

// stl
#include <string>
#include <iterator>
#include <vector>
#include <list>
#include <map>
using namespace std;

// boost
//#include <boost/signals2.hpp>
//using namespace boost;
//using namespace boost::signals2;

// cocos2d-x
#include <cocos2d.h>
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

using namespace cocosbuilder;

// protobuf
#include <google/protobuf/message.h>
using ::google::protobuf::Message;

#include "message.pb.h"

#include "Singleton.h"


//#include "DBCFileFactory.h"

typedef function<void(int,int)>  requestCallback;

#endif
