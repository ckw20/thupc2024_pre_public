#include<bits/stdc++.h>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io{
	int F(){
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	std::string S(){
		char buf[22];
		scanf("%s",buf);
		return std::string(buf);
	}
}
int n,m,k;
struct Command;
struct Robot{
	int id;
	Robot* hand[2];
	Command **command;
	void init(int _id);
	void activate();
	void chktrigger(int type);
}bot[111];
struct Command{
	int h;
	int type;
	virtual void packedexecute(Robot* robot,bool rev=0);
	virtual void execute(Robot* robot,bool rev=0) = 0;
	virtual bool chktrigger(int type);
	virtual Command* mirror();
	bool chkcnt();
	static const int SLACKOFF=1;
	static const int MOVE=2;
	static const int SWAP=4;
	static const int MIRROR=8;
	static const int REPLACE=16;
	static const int ACTIVATE=32;
	static const int TRIGGER=64;
};
Command* newcommand();
struct Slackoff: Command{
	Slackoff();
	virtual void execute(Robot* robot,bool rev=0);
};
struct Move: Command{
	int z;
	Move();
	virtual void execute(Robot* robot,bool rev=0);
};
struct Swap: Command{
	int x,y;
	Swap();
	virtual void execute(Robot* robot,bool rev=0);
};
struct Mirror: Command{
	int x;
	Mirror();
	virtual void execute(Robot* robot,bool rev=0);
};
struct Replace: Command{
	int x;
	Command* command;
	Replace();
	virtual void execute(Robot* robot,bool rev=0);
};
struct Activate: Command{
	Activate();
	virtual void execute(Robot* robot,bool rev=0);
};
struct Trigger: Command{
	int triggertype;
	Command* command;
	Trigger();
	virtual bool chktrigger(int type);
	virtual void packedexecute(Robot* robot,bool rev=0);
	virtual void execute(Robot* robot,bool rev=0);
};
struct Modified: Command{
	Command* const command;
	Modified(Command* _command);
	virtual bool chktrigger(int type);
	virtual void packedexecute(Robot* robot,bool rev=0);
	virtual void execute(Robot* robot,bool rev=0);
	virtual Command* mirror();
};

int main(){
	n=io::F(),m=io::F();
	k=io::F();
	for(int i=0;i<n;++i){
		bot[i].init(i);
	}
	while(1){
		for(int i=0;i<n;++i){
			bot[i].activate();
		}
	}
	return 0;
}

void Robot::init(int _id){
	id=_id;
	hand[0]=bot+io::F();
	hand[1]=bot+io::F();
	command=new Command*[m];
	for(int i=0;i<m;++i){
		command[i]=newcommand();
	}
}
void Robot::activate(){
	for(int i=0;i<m;++i){
		command[i]->packedexecute(this);
	}
}
void Robot::chktrigger(int type){
	if(hand[1]!=this){
		for(int i=0;i<m;++i){
			if(hand[1]->command[i]->chktrigger(type)){
				hand[1]->command[i]->execute(hand[1]);
				return;
			}
		}
	}
}
Command* newcommand(){
	std::string buf=io::S();
	if(buf=="SLACKOFF"){
		return new Slackoff;
	}
	if(buf=="MOVE"){
		return new Move;
	}
	if(buf=="SWAP"){
		return new Swap;
	}
	if(buf=="MIRROR"){
		return new Mirror;
	}
	if(buf=="REPLACE"){
		return new Replace;
	}
	if(buf=="ACTIVATE"){
		return new Activate;
	}
	if(buf=="TRIGGER"){
		return new Trigger;
	}
	assert(false);
}
void Command::packedexecute(Robot* robot,bool rev){
	bool ok=chkcnt();
	execute(robot,rev);
	if(ok){
		exit(0);
	}
	robot->chktrigger(type);
}
bool Command::chktrigger(int type){
	return 0;
}
Command* Command::mirror(){
	return new Modified(this);
}
bool Command::chkcnt(){
	if(--k==0){
		return true;
	}
	if(k<0){
		exit(0);
	}
	return false;
}
Slackoff::Slackoff(){
	type=SLACKOFF;
	h=0;
}
void Slackoff::execute(Robot* robot,bool rev){
	printf("Robot %d slacks off.\n",robot->id);
}
Move::Move(){
	type=MOVE;
	h=io::F();
	z=io::F();
}
void Move::execute(Robot* robot,bool rev){
	robot->hand[h^rev]=bot+(robot->hand[h^rev]->id+z)%n;
	printf("Robot %d moves its %s hand towards Robot %d.\n",robot->id,std::vector<std::string>{"left","right"}[h^rev].c_str(),robot->hand[h^rev]->id);
}
Swap::Swap(){
	type=SWAP;
	h=io::F();
	x=io::F()-1;
	y=io::F()-1;
}
void Swap::execute(Robot* robot,bool rev){
	printf("Robot %d swaps a line of command with Robot %d.\n",robot->id,robot->hand[h^rev]->id);
	std::swap(robot->command[y],robot->hand[h^rev]->command[x]);
}
Mirror::Mirror(){
	type=MIRROR;
	h=io::F();
	x=io::F()-1;
}
void Mirror::execute(Robot* robot,bool rev){
	printf("Robot %d modifies a line of command of Robot %d.\n",robot->id,robot->hand[h^rev]->id);
	robot->hand[h^rev]->command[x]=robot->hand[h^rev]->command[x]->mirror();
}
Replace::Replace(){
	type=REPLACE;
	h=io::F();
	x=io::F()-1;
	command=newcommand();
}
void Replace::execute(Robot* robot,bool rev){
	printf("Robot %d replaces a line of command of Robot %d.\n",robot->id,robot->hand[h^rev]->id);
	robot->hand[h^rev]->command[x]=command;
}
Activate::Activate(){
	type=ACTIVATE;
	h=io::F();
}
void Activate::execute(Robot* robot,bool rev){
	printf("Robot %d activates Robot %d.\n",robot->id,robot->hand[h^rev]->id);
	robot->hand[h^rev]->activate();
}
Trigger::Trigger(){
	type=TRIGGER;
	std::string buf=io::S();
	if(buf=="SLACKOFF:"){
		triggertype=SLACKOFF;
	}
	else if(buf=="MOVE:"){
		triggertype=MOVE;
	}
	else if(buf=="SWAP:"){
		triggertype=SWAP;
	}
	else if(buf=="MIRROR:"){
		triggertype=MIRROR;
	}
	else if(buf=="REPLACE:"){
		triggertype=REPLACE;
	}
	else if(buf=="ACTIVATE:"){
		triggertype=ACTIVATE;
	}
	else if(buf=="TRIGGER:"){
		triggertype=TRIGGER;
	}
	else assert(false);
	command=newcommand();
	command->type|=TRIGGER;
}
bool Trigger::chktrigger(int type){
	return triggertype&type;
}
void Trigger::packedexecute(Robot* robot,bool rev){
	return;
}
void Trigger::execute(Robot* robot,bool rev){
	command->packedexecute(robot,rev);
}
Modified::Modified(Command* _command):command(_command){
	type=command->type;
	h=1;
}
bool Modified::chktrigger(int type){
	return command->chktrigger(type);
}
void Modified::packedexecute(Robot* robot,bool rev){
	command->packedexecute(robot,h^rev);
}
void Modified::execute(Robot* robot,bool rev){
	command->execute(robot,h^rev);
}
Command* Modified::mirror(){
	h^=1;
	return this;
}