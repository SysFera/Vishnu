/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class EJobList {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected EJobList(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(EJobList obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_EJobList(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void insert_all(EJobList _q) {
    VISHNUJNI.EJobList_insert_all(swigCPtr, this, EJobList.getCPtr(_q), _q);
  }

  public void insert_at(long _pos, Job _obj) {
    VISHNUJNI.EJobList_insert_at(swigCPtr, this, _pos, Job.getCPtr(_obj), _obj);
  }

  public Job at(long _index) {
    long cPtr = VISHNUJNI.EJobList_at(swigCPtr, this, _index);
    return (cPtr == 0) ? null : new Job(cPtr, false);
  }

  public Job get(long _index) {
    long cPtr = VISHNUJNI.EJobList_get(swigCPtr, this, _index);
    return (cPtr == 0) ? null : new Job(cPtr, false);
  }

  public void push_back(Job _obj) {
    VISHNUJNI.EJobList_push_back(swigCPtr, this, Job.getCPtr(_obj), _obj);
  }

  public long size() {
    return VISHNUJNI.EJobList_size(swigCPtr, this);
  }

  public void clear() {
    VISHNUJNI.EJobList_clear(swigCPtr, this);
  }

}
