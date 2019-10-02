/*
 * author: Xialiang Dou
 * C++ implementation of unevenly spaced (and sized) time series rolling operators by Andreas Eckner.
 * For the reference, see echner.com.
 */

#include <set>
#include <vector>
#include <list>
#include <utility>
#include <deque>

namespace RollingTools{
  //RollingOperatror each time update item with a pair T1, T2. T1 is the value of the item and T2 is the quantity.
  template<class T1, class T2>
  class RollingTool{
  public:
    RollingTool(){}
    virtual ~RollingTool(){}
    virtual void push() = 0;
    virtual T1 getStat() = 0;
  };//class RollingTool

  template<class T1, class T2>
  class RollingMean : public RollingTool<T1, T2>{
    T2 m_maxSize = 10;
    T2 m_curSize = 0;
    T1 m_wSum = 0;
    std::list<std::pair<T1, T2>> m_tracker;


    void pop() {
      while(m_curSize > m_maxSize) {
	m_curSize -= m_tracker.front().second;
	m_wSum -= m_tracker.front().first * m_tracker.front().second;
	m_tracker.pop_front();
      }
    }
  public:
    RollingMean(){}
    RollingMean(T2 _maxSize):m_maxSize(_maxSize){}
    ~RollingMean(){}
    void push(T1 _value, T2 _size) {
      m_curSize += _size;
      m_tracker.push_back(make_pair(_value, _size));
      m_wSum += _value * _size;
      pop();
    }
    T1 getStat() {
      return m_wSum / m_curSize;
      return m_wSum / m_curSize;
    }
  };//class Rolling Mean
  template <class T1, class T2>
  class RollingExtreme : public RollingTool<T1, T2> {
    std::list<std::pair<T1, T2>> m_tracker;
    std::deque<std::pair<T1, T2>> m_extremeTracker;
    T2 m_maxSize = 10;
    T2 m_curSize = 0;
    void pop() {
      while(m_curSize > m_maxSize) {
	m_curSize -= m_tracker.front().second;
	if (m_tracker.front() == m_extremeTracker.front()) {
	  m_extremeTracker.pop_front();
	}
	m_tracker.pop_front();
      }
    }
  public:
    RollingExtreme(){}
    RollingExtreme(T2 _maxSize): m_maxSize(_maxSize){}
    ~RollingExtreme(){}

  };
}//namespace RollingTool
