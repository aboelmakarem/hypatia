#include "stdio.h"
#include "stdlib.h"
#include "list"
#include "float.h"

double Factorial(const int& iNumber)
{
	if(iNumber <= 1)		return 1.0;
	if(iNumber == 2)		return 2.0;
	if(iNumber == 3)		return 6.0;
	if(iNumber == 4)		return 24.0;
	if(iNumber == 5)		return 120.0;
	if(iNumber == 6)		return 720.0;
	if(iNumber == 7)		return 5040.0;
	if(iNumber == 8)		return 40320.0;
	if(iNumber == 9)		return 362880.0;
	if(iNumber == 10)		return 3628800.0;
	if(iNumber == 11)		return 39916800.0;
	if(iNumber == 12)		return 479001600.0;
	if(iNumber == 13)		return 6227020800.0;
	if(iNumber == 14)		return 87178291200.0;
	if(iNumber == 15)		return 1307674368000.0;
	if(iNumber == 16)		return 20922789888000.0;
	if(iNumber == 17)		return 355687428096000.0;
	if(iNumber == 18)		return 6402373705728000.0;
	if(iNumber == 19)		return 121645100408832000.0;
	if(iNumber == 20)		return 2432902008176640000.0;
	unsigned int i = 0;
	double dFactorial = 2432902008176640000.0;
	for(i = 21 ; i <= iNumber ; i++)
	{
		dFactorial = dFactorial*(double)i;
	}
	return dFactorial;
}

enum ActionType
{
	NullActionType = 0,
	TicTacToeActionType = 1
};

enum StateType
{
	NullStateType = 0,
	TicTacToeStateType = 1
};

class Action
{
public:
	virtual ActionType GetType() const = 0;
private:

protected:

};

class State
{
public:
	virtual StateType GetType() const = 0;
	virtual bool IsTerminal() const = 0;
	virtual double GetUtility() const = 0;
	virtual void GetActions(std::list<Action*>& lpoActions) const = 0;
	virtual State* GetResultState(Action* poAction) const = 0;
	virtual int GetPlayer() const = 0;
	virtual void Show() const = 0;
	
private:

protected:

};

class TicTacToeAction : public Action
{
public:
	TicTacToeAction();
	TicTacToeAction(const unsigned int& iRow,const unsigned int& iColumn);
	TicTacToeAction(const TicTacToeAction& oAction);
	~TicTacToeAction();
	TicTacToeAction& operator=(const TicTacToeAction& oAction);
	void Reset();
	ActionType GetType() const;
	void Set(const unsigned int& iRow,const unsigned int& iColumn);
	unsigned int GetRow() const;
	unsigned int GetColumn() const;
	
private:
	
	
protected:
	void Initialize();
	unsigned int m_iRow;
	unsigned int m_iColumn;
};

class TicTacToeState : public State
{
public:
	TicTacToeState(const unsigned int& iBoardSize);
	TicTacToeState(const TicTacToeState& oState);
	~TicTacToeState();
	TicTacToeState& operator=(const TicTacToeState& oState);
	void Reset();
	StateType GetType() const;
	bool IsTerminal() const;
	double GetUtility() const;
	void GetActions(std::list<Action*>& lpoActions) const;
	State* GetResultState(Action* poAction) const;
	int GetPlayer() const;
	bool IsValidAction(Action* poAction) const;
	void Show() const;
	static double GetStateCount(const unsigned int iBoardSize);
	
private:
	TicTacToeState();
	
protected:
	void Initialize();
	void Allocate(const unsigned int& iBoardSize);
	unsigned int GetXCount() const;
	unsigned int GetOCount() const;
	unsigned int GetEmptyCount() const;
	bool IsRowWin(const unsigned int& iRowNumber,const int& iWinningSide) const;
	bool IsColumnWin(const unsigned int& iColumnNumber,const int& iWinningSide) const;
	bool IsDiagonalWin(const int& iWinningSide) const;
	bool DidSideWin(const int& iWinningSide) const;
	int* m_piData;
	unsigned int m_iSize;
};

TicTacToeAction::TicTacToeAction()
{
	Initialize();
}
TicTacToeAction::TicTacToeAction(const unsigned int& iRow,const unsigned int& iColumn)
{
	Initialize();
	m_iRow = iRow;
	m_iColumn = iColumn;
}
TicTacToeAction::TicTacToeAction(const TicTacToeAction& oAction)
{
	*this = oAction;
}
TicTacToeAction::~TicTacToeAction()
{
	Reset();
}
TicTacToeAction& TicTacToeAction::operator=(const TicTacToeAction& oAction)
{
	m_iRow = oAction.m_iRow;
	m_iColumn = oAction.m_iColumn;
	return *this;
}
void TicTacToeAction::Reset()
{
	Initialize();
}
ActionType TicTacToeAction::GetType() const
{
	return TicTacToeActionType;
}
void TicTacToeAction::Set(const unsigned int& iRow,const unsigned int& iColumn)
{
	m_iRow = iRow;
	m_iColumn = iColumn;
}
unsigned int TicTacToeAction::GetRow() const
{
	return m_iRow;
}
unsigned int TicTacToeAction::GetColumn() const
{
	return m_iColumn;
}
void TicTacToeAction::Initialize()
{
	m_iRow = 0;
	m_iColumn = 0;
}

TicTacToeState::TicTacToeState()
{
	Initialize();
}
TicTacToeState::TicTacToeState(const unsigned int& iBoardSize)
{
	Allocate(iBoardSize);
}
TicTacToeState::TicTacToeState(const TicTacToeState& oState)
{
	Initialize();
	*this = oState;
}
TicTacToeState::~TicTacToeState()
{
	Reset();
}
TicTacToeState& TicTacToeState::operator=(const TicTacToeState& oState)
{
	Reset();
	Allocate(oState.m_iSize);
	unsigned int i = 0;
	unsigned int iSize = m_iSize*m_iSize;
	for(i = 0 ; i < iSize ; i++)
	{
		m_piData[i] = oState.m_piData[i];
	}
	return *this;
}
void TicTacToeState::Reset()
{
	if(m_piData != 0)		delete [] m_piData;
	m_iSize = 0;
}
StateType TicTacToeState::GetType() const
{
	return TicTacToeStateType;
}
bool TicTacToeState::IsTerminal() const
{
	// all full states are true states
	if(GetEmptyCount() == 0)		return true;
	// if it is not empty but it is a win for X, then it is a terminal state
	if(DidSideWin(1))				return true;
	// if it is not empty but it is a win for Y, then it is a terminal state
	if(DidSideWin(-1))				return true;
	return false;
}
double TicTacToeState::GetUtility() const
{
	if(DidSideWin(1))		return 1.0;
	if(DidSideWin(-1))		return -1.0;
	return 0.0;
}
void TicTacToeState::GetActions(std::list<Action*>& lpoActions) const
{
	unsigned int i = 0;
	unsigned int j = 0;
	for(i = 0 ; i < m_iSize ; i++)
	{
		for(j = 0 ; j < m_iSize ; j++)
		{
			if(m_piData[m_iSize*i + j] == 0)		lpoActions.push_back(new TicTacToeAction(i,j));
		}
	}
}
State* TicTacToeState::GetResultState(Action* poAction) const
{
	if(!IsValidAction(poAction))						return 0;
	TicTacToeState* poResultState = new TicTacToeState(*this);
	int iSide = -1;
	if(GetXCount() == GetOCount())		iSide = 1;
	TicTacToeAction* poTTTAction = (TicTacToeAction*)poAction;
	poResultState->m_piData[m_iSize*poTTTAction->GetRow() + poTTTAction->GetColumn()] = iSide;
	return poResultState;
}
int TicTacToeState::GetPlayer() const
{
	// if there is an equal number of X's and O's, then it is X's turn
	if(GetXCount() == GetOCount())		return 1;
	// otherwise, it is O's turn
	return -1;
}
bool TicTacToeState::IsValidAction(Action* poAction) const
{
	if(poAction->GetType() != TicTacToeActionType)		return false;
	TicTacToeAction* poTTTAction = (TicTacToeAction*)poAction;
	unsigned int iRow = poTTTAction->GetRow();
	unsigned int iColumn = poTTTAction->GetColumn();
	if(iRow >= m_iSize)									return false;
	if(iColumn >= m_iSize)								return false;
	if(m_piData[m_iSize*iRow + iColumn] != 0)			return false;
	return true;
}
void TicTacToeState::Show() const
{
	unsigned int i = 0;
	unsigned int j = 0;
	printf("   ");
	for(i = 0 ; i < m_iSize ; i++)
	{
		printf(" %d  ",i + 1);
	}
	printf("\n   --- --- --- \n");
	for(i = 0 ; i < m_iSize ; i++)
	{
		printf("%d ",i + 1);
		for(j = 0 ; j < m_iSize ; j++)
		{
			if(m_piData[m_iSize*i + j] == -1)		printf("| O ");
			if(m_piData[m_iSize*i + j] == 0)		printf("|   ");
			if(m_piData[m_iSize*i + j] == 1)		printf("| X ");
		}
		printf("| %d\n",i + 1);
		if(i < (m_iSize - 1))
		{
			printf("  ----");
			for(j = 1 ; j < m_iSize ; j++)
			{
				printf("+---");
			}
			printf("-\n");
		}
	}
	for(j = 1 ; j < m_iSize ; j++)
	{
		//printf("+---");
	}
			
	//printf("   --- --- --- \n");
	for(j = 1 ; j < m_iSize ; j++)
	{
		printf("   --- ");
	}
	printf("\n   ");
	for(i = 0 ; i < m_iSize ; i++)
	{
		printf(" %d  ",i + 1);
	}
	printf("\n");
}
double TicTacToeState::GetStateCount(const unsigned int iBoardSize)
{
	// the number of distinct states in a tic-tac-toe game is given by
	// sum_m,n [s!/(s - m - n)!/m!/n!]
	// where s = k*k and k is the board size
	// where m runs from 0 to (s+1)/2
	// n can be equal to m or one less than m
	unsigned int iSize = iBoardSize*iBoardSize;
	double dSFactorial = Factorial(iSize);
	unsigned int m = 0;
	unsigned int iMaXM = (iSize + 1)/2;
	double dCount = 0.0;
	for(m = 0 ; m <= iMaXM ; m++)
	{
		if(m == 0)				dCount += 1.0;
		else if(m == iMaXM)		dCount += dSFactorial/(Factorial(iMaXM - 1)*Factorial(iMaXM));
		else
		{
			dCount += dSFactorial/(Factorial(iSize - m - (m - 1))*Factorial(m - 1)*Factorial(m));
			dCount += dSFactorial/(Factorial(iSize - 2*m)*Factorial(m)*Factorial(m));
		}
	}
	return dCount;
}
void TicTacToeState::Initialize()
{
	m_piData = 0;
	m_iSize = 0;
}
void TicTacToeState::Allocate(const unsigned int& iBoardSize)
{
	m_iSize = iBoardSize;
	unsigned int iSize = m_iSize*m_iSize;
	m_piData = new int[iSize];
	unsigned int i = 0;
	for(i = 0 ; i < iSize ; i++)
	{
		m_piData[i] = 0;
	}
}
unsigned int TicTacToeState::GetXCount() const
{
	unsigned int i = 0;
	unsigned int iSize = m_iSize*m_iSize;
	unsigned int iCount = 0;
	for(i = 0 ; i < iSize ; i++)
	{
		if(m_piData[i] == 1)		iCount++;
	}
	return iCount;
}
unsigned int TicTacToeState::GetOCount() const
{
	unsigned int i = 0;
	unsigned int iSize = m_iSize*m_iSize;
	unsigned int iCount = 0;
	for(i = 0 ; i < iSize ; i++)
	{
		if(m_piData[i] == -1)		iCount++;
	}
	return iCount;
}
unsigned int TicTacToeState::GetEmptyCount() const
{
	unsigned int i = 0;
	unsigned int iSize = m_iSize*m_iSize;
	unsigned int iCount = 0;
	for(i = 0 ; i < iSize ; i++)
	{
		if(m_piData[i] == 0)		iCount++;
	}
	return iCount;
}
bool TicTacToeState::IsRowWin(const unsigned int& iRowNumber,const int& iWinningSide) const
{
	unsigned int i = 0;
	for(i = 0 ; i < m_iSize ; i++)
	{
		if(m_piData[m_iSize*iRowNumber + i] != iWinningSide)
		{
			return false;
		}
	}
	return true;
}
bool TicTacToeState::IsColumnWin(const unsigned int& iColumnNumber,const int& iWinningSide) const
{
	unsigned int i = 0;
	for(i = 0 ; i < m_iSize ; i++)
	{
		if(m_piData[m_iSize*i + iColumnNumber] != iWinningSide)
		{
			return false;
		}
	}
	return true;
}
bool TicTacToeState::IsDiagonalWin(const int& iWinningSide) const
{
	unsigned int i = 0;
	bool bWon = true;
	for(i = 0 ; i < m_iSize ; i++)
	{
		if(m_piData[m_iSize*i + i] != iWinningSide)
		{
			bWon = false;
		}
	}
	if(!bWon)
	{
		for(i = 0 ; i < m_iSize ; i++)
		{
			if(m_piData[m_iSize*i + (m_iSize - i - 1)] != iWinningSide)
			{
				return false;
			}
		}
	}
	return true;
}
bool TicTacToeState::DidSideWin(const int& iWinningSide) const
{
	unsigned int i = 0;
	unsigned int j = 0;
	for(i = 0 ; i < m_iSize ; i++)
	{
		for(j = 0 ; j < m_iSize ; j++)
		{
			if(m_piData[m_iSize*i + j] == iWinningSide)
			{
				if(IsRowWin(i,iWinningSide))			return true;
				if(IsColumnWin(j,iWinningSide))			return true;
			}
		}
	}
	return IsDiagonalWin(iWinningSide);
}

double MaxValue(State* poState);
double MinValue(State* poState);
Action* MiniMaxAction(State* poState);

Action* MiniMaxAction(State* poState)
{
	if(poState->IsTerminal())		return 0;
	std::list<Action*> lpoActions;
	poState->GetActions(lpoActions);
	std::list<Action*>::iterator liActions;
	double dTemp = 0.0;
	State* poResultState = 0;
	Action* poTargetAction = 0;
	bool bMaximize = true;
	if(poState->GetPlayer() < 0)		bMaximize = false;
	double dTargetOptimizer = -DBL_MAX;
	if(!bMaximize)		dTargetOptimizer = DBL_MAX;
	for(liActions = lpoActions.begin() ; liActions != lpoActions.end() ; liActions++)
	{
		poResultState = poState->GetResultState((*liActions));
		if(bMaximize)		dTemp = MinValue(poResultState);
		else				dTemp = MaxValue(poResultState);
		delete poResultState;
		if((bMaximize && (dTemp > dTargetOptimizer)) || ((!bMaximize) && (dTemp < dTargetOptimizer)))
		{
			dTargetOptimizer = dTemp;
			poTargetAction = (*liActions);
		}
	}
	// now we the target value action, delete all other actions
	for(liActions = lpoActions.begin() ; liActions != lpoActions.end() ; liActions++)
	{
		if(poTargetAction != (*liActions))		delete (*liActions);
	}
	lpoActions.clear();
	return poTargetAction;
}

double MaxValue(State* poState)
{
	if(poState->IsTerminal())		return poState->GetUtility();
	std::list<Action*> lpoActions;
	poState->GetActions(lpoActions);
	std::list<Action*>::iterator liActions;
	double dMax = -DBL_MAX;
	double dTemp = 0.0;
	State* poResultState = 0;
	for(liActions = lpoActions.begin() ; liActions != lpoActions.end() ; liActions++)
	{
		poResultState = poState->GetResultState((*liActions));
		dTemp = MinValue(poResultState);
		delete poResultState;
		if(dTemp > dMax)
		{
			dMax = dTemp;
		}
		delete (*liActions);
	}
	return dMax;
}

double MinValue(State* poState)
{
	if(poState->IsTerminal())		return poState->GetUtility();
	std::list<Action*> lpoActions;
	poState->GetActions(lpoActions);
	std::list<Action*>::iterator liActions;
	double dMin = DBL_MAX;
	double dTemp = 0.0;
	State* poResultState = 0;
	for(liActions = lpoActions.begin() ; liActions != lpoActions.end() ; liActions++)
	{
		poResultState = poState->GetResultState((*liActions));
		dTemp = MaxValue(poResultState);
		delete poResultState;
		if(dTemp < dMin)
		{
			dMin = dTemp;
		}
		delete (*liActions);
	}
	return dMin;
}

int main(int argc,char** argv)
{
	if(argc < 2)
	{
		printf("error: missing board size\n");
		printf("usage: tictactoe n\n");
		printf("where n is the board size\n");
		return 1;
	}
	unsigned int iBoardSize = atoi(argv[1]);
	printf("number of distinct states for this size is %lf\n",TicTacToeState::GetStateCount(iBoardSize));
	TicTacToeState* poState = new TicTacToeState(iBoardSize);
	TicTacToeState* poNewState = 0;
	TicTacToeAction oAction;
	TicTacToeAction* poMyAction;
	unsigned int iRow = 0;
	unsigned int iColumn = 0;
	while(true)
	{
		poState->Show();
		if(poState->IsTerminal())		break;
		printf("your turn\n");
		scanf("%d %d",&iRow,&iColumn);
		oAction.Set(iRow - 1,iColumn - 1);
		if(!poState->IsValidAction(&oAction))
		{
			printf("invalid move\n");
			continue;
		}
		poNewState = (TicTacToeState*)(poState->GetResultState(&oAction));
		delete poState;
		poState = poNewState;
		
		// now it is the computer's turn
		poState->Show();
		if(poState->IsTerminal())		break;
		printf("my turn\n");
		poMyAction = (TicTacToeAction*)(MiniMaxAction(poState));
		poNewState = (TicTacToeState*)(poState->GetResultState(poMyAction));
		delete poMyAction;
		delete poState;
		poState = poNewState;
	};
	double dTerminalStateUtility = poState->GetUtility();
	if(dTerminalStateUtility == 1)				printf("you won\n");
	else if(dTerminalStateUtility == -1)		printf("I won\n");
	else										printf("it is a draw, nice game\n");
	delete poState;
	return 0;
}

