//
//  DDFieldIterator.h
//  DynamicData
//
//  Created by mich2 on 11/1/12.
//  Copyright (c) 2012 -. All rights reserved.
//

#ifndef DynamicData_DDFieldIterator_h
#define DynamicData_DDFieldIterator_h

//TODO make two classes for the two fields.
template<typename IdxType, class Field, class CachedElement>
class DDFieldIterator
{
public:
    
    DDFieldIterator(Field& field) :
        _field(field),
        _currIdx(0)
    {}
    
    virtual ~DDFieldIterator() {}
    
    DDFieldIterator(const DDFieldIterator&) = delete;
    const DDFieldIterator& operator=(const DDFieldIterator&) = delete;
    
    
    void startItr()
    {
        _boundaryItr = _field.beginItr();
        _currIdx = 0;
    }
    
    std::tuple<IdxType, bool, IdxType> itrEvalAndStep()
    {
        std::tuple<IdxType, bool, IdxType> res = _field.eval(_currIdx, _boundaryItr);
        _currIdx++;
        
        return res;
    }
    
    /*
    //TODO remove?
    IdxType itrEvalAndStep(bool& hasCacheElement, CachedElement& cachedElement)
    {
        IdxType res = _field.eval(_currIdx, _boundaryItr, hasCacheElement, cachedElement);
        _currIdx++;
        
        return res;
    }
    */
    
    //TODO check this!
    IdxType itrEval(IdxType idx, bool& hasCacheElement, CachedElement& cachedElement)
    {
        if (idx < _currIdx) assert(0);
        _currIdx = idx;
        
        IdxType res = _field.eval(_currIdx, _boundaryItr, hasCacheElement, cachedElement);
        //_currIdx++;
        
        return res;
    }
    
    void reset()
    {
        _currIdx = 0;
    }
    
private:
    Field& _field;
    IdxType _currIdx;
    typename Field::BoundItr _boundaryItr;
};

#endif