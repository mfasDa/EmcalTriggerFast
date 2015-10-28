#ifndef TRIGGERBADCHANNELCONTAINER_H
#define TRIGGERBADCHANNELCONTAINER_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <vector>

/**
 * @struct TriggerBadChannelContainer
 * @brief Structure for position of trigger channels
 *
 * This structure is a container for trigger channels in col-row space with
 * a given mask. Channels can only be added to the container, or it can be
 * checked whether the channel is listed in the container.
 */
class TriggerBadChannelContainer {
public:

  /**
   * @struct TriggerChannelPosition
   * @brief 2D position of a trigger channel on the EMCAL surface
   *
   * This class represents the position of a trigger channel in a 2D coordinate
   * system consisting of column and row.
   */
  class TriggerChannelPosition {
  public:

    /**
     * Dummy (I/O) constructor, not to be used
     */
    TriggerChannelPosition(): fCol(-1), fRow(-1) { }

    /**
     * Main constuctor, setting the position in column and row
     * @param col Column of the trigger channel
     * @param row Row of the trigger channel
     */
    TriggerChannelPosition(int col, int row): fCol(col), fRow(row) { }

    /**
     * Destructor, nothing to do
     */
    virtual ~TriggerChannelPosition() {}

    /**
     * Get the column of the channel
     * @return  The column of the channel
     */
    int GetCol() const { return fCol; }

    /**
     * Get the row of the channel
     * @return The row of the channel
     */
    int GetRow() const { return fRow; }

    /**
     * Set the colummn of the channel
     * \param col The column of the channel
     */
    void SetCol(int col) { fCol = col; }

    /**
     * Set the row of the channel
     * @param row The row of the channel
     */
    void SetRow(int row) { fRow = row; }

    /**
     * Check if the object is equal to object ref. Object can only be equal if ref is of
     * the same type (AliEmcalTrigger channel position). If this is the case, col and row
     * of the two objects have to match.
     * @param ref The object to check
     * @return True if objects are equal, false otherwise
     */
    bool operator==(const TriggerChannelPosition &ref) const;

    /**
     * Compare objects. If objects differ, return always greater (+1). Otherwise compare col and
     * row of the object. Col has priority with respect to row.
     * @param ref The object ot comparte to
     * @return 0 if objects are equal, -1 if this object is smaller, +1 if this object is larger.
     */
    bool operator<(const TriggerChannelPosition &other) const;

  private:
    int	   	                fCol;            ///< Column of the trigger channel
    int 	                fRow;            ///< Row of the trigger channel
  };

  /**
   * Constructor
   */
  TriggerBadChannelContainer(): fChannels() {}

  /**
   * Destructor, cleans up the container
   */
  virtual ~TriggerBadChannelContainer(){}

  /**
   * Add a new channel with the postion in column and row to the container, In case the channel
   * is already listed in the trigger channel container we don't add it again.
   * @param col Column of the channel
   * @param row Row of the channel
   */
  void AddChannel(int col, int row);

  /**
   * Check whether channel with the position (col, row) is listed in the trigger channel container
   * @param col Column of the channel
   * @param row Row of the channel
   * @return True if the channel is listed, false otherwise
   */
  bool HasChannel(int col, int row);

private:
  std::vector<TriggerChannelPosition>             fChannels;      ///< Container for listed channels
};

#endif
