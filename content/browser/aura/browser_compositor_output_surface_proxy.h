// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_AURA_BROWSER_COMPOSITOR_OUTPUT_SURFACE_PROXY_H_
#define CONTENT_BROWSER_AURA_BROWSER_COMPOSITOR_OUTPUT_SURFACE_PROXY_H_

#include "base/memory/ref_counted.h"
#include "base/time/time.h"
#include "content/browser/aura/refcounted_id_map.h"

namespace base { class SingleThreadTaskRunner; }

namespace IPC { class Message; }

namespace content {
class BrowserCompositorOutputSurface;

// Directs vsync updates to the appropriate BrowserCompositorOutputSurface.
class BrowserCompositorOutputSurfaceProxy
    : public base::RefCountedThreadSafe<BrowserCompositorOutputSurfaceProxy> {
 public:
  BrowserCompositorOutputSurfaceProxy(
      RefCountedIDMap<BrowserCompositorOutputSurface>* surface_map);

  // Call this before each OutputSurface is created to ensure that the
  // proxy is connected to the current host.
  void ConnectToGpuProcessHost(
      base::SingleThreadTaskRunner* compositor_thread_task_runner);

 private:
  friend class base::RefCountedThreadSafe<BrowserCompositorOutputSurfaceProxy>;
  ~BrowserCompositorOutputSurfaceProxy();

  void OnMessageReceivedOnCompositorThread(const IPC::Message& message);

  void OnUpdateVSyncParametersOnCompositorThread(int surface_id,
                                                 base::TimeTicks timebase,
                                                 base::TimeDelta interval);

  RefCountedIDMap<BrowserCompositorOutputSurface>* surface_map_;
  bool connected_to_gpu_process_host_;

  DISALLOW_COPY_AND_ASSIGN(BrowserCompositorOutputSurfaceProxy);
};

}  // namespace content

#endif  // CONTENT_BROWSER_AURA_BROWSER_COMPOSITOR_OUTPUT_SURFACE_PROXY_H_