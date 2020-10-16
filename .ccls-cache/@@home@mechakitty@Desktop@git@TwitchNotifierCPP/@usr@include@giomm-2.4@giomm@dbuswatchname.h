// Generated by gmmproc 2.64.2 -- DO NOT MODIFY!
#ifndef _GIOMM_DBUSWATCHNAME_H
#define _GIOMM_DBUSWATCHNAME_H


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 2 -*-

/* Copyright (C) 2010 The giomm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <giomm/dbusconnection.h>


namespace Gio
{

namespace DBus
{

/** @addtogroup giommEnums giomm Enums and Flags */

/** 
 *  @var BusNameWatcherFlags BUS_NAME_WATCHER_FLAGS_NONE
 * No flags set.
 * 
 *  @var BusNameWatcherFlags BUS_NAME_WATCHER_FLAGS_AUTO_START
 * If no-one owns the name when
 * beginning to watch the name, ask the bus to launch an owner for the
 * name.
 * 
 *  @enum BusNameWatcherFlags
 * 
 * Flags used in g_bus_watch_name().
 * 
 * @newin{2,26}
 *
 * @ingroup giommEnums
 * @par Bitwise operators:
 * <tt>%BusNameWatcherFlags operator|(BusNameWatcherFlags, BusNameWatcherFlags)</tt><br>
 * <tt>%BusNameWatcherFlags operator&(BusNameWatcherFlags, BusNameWatcherFlags)</tt><br>
 * <tt>%BusNameWatcherFlags operator^(BusNameWatcherFlags, BusNameWatcherFlags)</tt><br>
 * <tt>%BusNameWatcherFlags operator~(BusNameWatcherFlags)</tt><br>
 * <tt>%BusNameWatcherFlags& operator|=(BusNameWatcherFlags&, BusNameWatcherFlags)</tt><br>
 * <tt>%BusNameWatcherFlags& operator&=(BusNameWatcherFlags&, BusNameWatcherFlags)</tt><br>
 * <tt>%BusNameWatcherFlags& operator^=(BusNameWatcherFlags&, BusNameWatcherFlags)</tt><br>
 */
enum BusNameWatcherFlags
{
  BUS_NAME_WATCHER_FLAGS_NONE = 0x0,
  BUS_NAME_WATCHER_FLAGS_AUTO_START = (1<<0)
};

/** @ingroup giommEnums */
inline BusNameWatcherFlags operator|(BusNameWatcherFlags lhs, BusNameWatcherFlags rhs)
  { return static_cast<BusNameWatcherFlags>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs)); }

/** @ingroup giommEnums */
inline BusNameWatcherFlags operator&(BusNameWatcherFlags lhs, BusNameWatcherFlags rhs)
  { return static_cast<BusNameWatcherFlags>(static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs)); }

/** @ingroup giommEnums */
inline BusNameWatcherFlags operator^(BusNameWatcherFlags lhs, BusNameWatcherFlags rhs)
  { return static_cast<BusNameWatcherFlags>(static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs)); }

/** @ingroup giommEnums */
inline BusNameWatcherFlags operator~(BusNameWatcherFlags flags)
  { return static_cast<BusNameWatcherFlags>(~static_cast<unsigned>(flags)); }

/** @ingroup giommEnums */
inline BusNameWatcherFlags& operator|=(BusNameWatcherFlags& lhs, BusNameWatcherFlags rhs)
  { return (lhs = static_cast<BusNameWatcherFlags>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs))); }

/** @ingroup giommEnums */
inline BusNameWatcherFlags& operator&=(BusNameWatcherFlags& lhs, BusNameWatcherFlags rhs)
  { return (lhs = static_cast<BusNameWatcherFlags>(static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs))); }

/** @ingroup giommEnums */
inline BusNameWatcherFlags& operator^=(BusNameWatcherFlags& lhs, BusNameWatcherFlags rhs)
  { return (lhs = static_cast<BusNameWatcherFlags>(static_cast<unsigned>(lhs) ^ static_cast<unsigned>(rhs))); }


/** For example,
 * void on_name_appeared(const Glib::RefPtr<Gio::DBus::Connection>& connection,
 * const Glib::ustring& name, const Glib::ustring& name_owner);
 * @ingroup DBus
 */
using SlotNameAppeared = sigc::slot<void, const Glib::RefPtr<Gio::DBus::Connection>&, Glib::ustring, const Glib::ustring&>;

/** For example,
 * void on_name_vanished(const Glib::RefPtr<Gio::DBus::Connection>& connection,
 * const Glib::ustring& name);
 * @ingroup DBus
 */
using SlotNameVanished = sigc::slot<void, const Glib::RefPtr<Gio::DBus::Connection>&, Glib::ustring>;

//TODO: Add example from C API in class docs?
/** Starts watching @a name on the bus specified by @a bus_type and calls
 * @a name_appeared_slot and @a name_vanished_slot when the name is
 * known to have a owner respectively known to lose its owner. Callbacks will
 * be invoked in the thread-default main loop of the thread you are calling
 * this function from.
 *
 * You are guaranteed that one of the slot will be invoked after calling
 * this function. When you are done watching the name, just call
 * unwatch_name() with the watcher id this function returns.
 *
 * If the name vanishes or appears (for example the application owning the
 * name could restart), the slot are also invoked. If the Connection
 * that is used for watching the name disconnects, then @a
 * name_vanished_slot is invoked since it is no longer possible to access
 * the name.
 *
 * Another guarantee is that invocations of @a name_appeared_slot and @a
 * name_vanished_slot are guaranteed to alternate; that is, if
 * @a name_appeared_slot is invoked then you are guaranteed that the next
 * time one of the slot is invoked, it will be @a name_vanished_slot.
 * The reverse is also true.
 *
 * This behavior makes it very simple to write applications that wants to take
 * action when a certain name exists, see the C API's Example 9, “Simple
 * application watching a name” for more information. Basically, the
 * application should create object proxies in @a name_appeared_slot and
 * destroy them again (if any) in @a name_vanished_slot.
 *
 * @param bus_type The type of bus to watch a name on.
 * @param name The name (well-known or unique) to watch.
 * @param name_appeared_slot Slot to invoke when name is known to exist.
 * @param name_vanished_slot Slot to invoke when name is known to not
 * exist.
 * @param flags Flags from the BusNameWatcherFlags enumeration.
 * @return An identifier (never 0) that can be used with unwatch_name() to
 * stop watching the name.
 *
 * @newin{2,28}
 * @ingroup DBus
 */
GIOMM_API
guint watch_name(
  BusType bus_type,
  const Glib::ustring& name,
  const SlotNameAppeared& name_appeared_slot = SlotNameAppeared(),
  const SlotNameVanished& name_vanished_slot = SlotNameVanished(),
  BusNameWatcherFlags flags = Gio::DBus::BUS_NAME_WATCHER_FLAGS_NONE
);


/** A watch_name() function that takes a Connection instead of a BusType.
 *
 * @param connection A Connection.
 * @param name The name (well-known or unique) to watch.
 * @param name_appeared_slot Slot to invoke when name is known to exist.
 * @param name_vanished_slot Slot to invoke when name is known to not
 * exist.
 * @param flags Flags from the BusNameWatcherFlags enumeration.
 * @return An identifier (never 0) that can be used with unwatch_name() to
 * stop watching the name.
 *
 * @newin{2,28}
 * @ingroup DBus
 */
GIOMM_API
guint watch_name(
  const Glib::RefPtr<Connection>& connection,
  const Glib::ustring& name,
  const SlotNameAppeared& name_appeared_slot = SlotNameAppeared(),
  const SlotNameVanished& name_vanished_slot = SlotNameVanished(),
  BusNameWatcherFlags flags = Gio::DBus::BUS_NAME_WATCHER_FLAGS_NONE
);


/** Stops watching a name.
 * @param watcher_id An identifier obtained from watch_name().
 * @ingroup DBus
 */
GIOMM_API
void unwatch_name(guint watcher_id);


} // namespace DBus

} // namespace Gio


#endif /* _GIOMM_DBUSWATCHNAME_H */

