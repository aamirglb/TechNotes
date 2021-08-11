import gi
gi.require_version('Gst','1.0')
from gi.repository import Gst,GstController
#global variables 
#the values of a,b,c get updated for certain events dynamically based on external hardware 
a = 0 
b = 0 
c = 0 
source = Gst.ElementFactory.make("gltestsrc", "source") 
gltrnsfrm = Gst.ElementFactory.make("gltransformation","gltrnsfrm") 
sink = Gst.ElementFactory.make("glimagesink", "sink") 
# create the empty pipeline 
pipeline = Gst.Pipeline.new("test-pipeline") 
if not pipeline or not source or not gltrnsfrm or not sink: 
	print("ERROR: Not all elements could be created") 
	sys.exit(1) 
# build the pipeline 
pipeline.add(source,gltrnsfrm,sink) 
if not source.link(gltrnsfrm): 
	print("ERROR: Could not link source to gltrsnfrm") 
	sys.exit(1) 
if not gltrnsfrm.link(sink): 
   print("ERROR: Could not link gltrsnfrm  to sink") 
   sys.exit(1) 
# modify the gltransformation's properties 
gltrnsfrm.set_property("rotation-z",a) 
gltrnsfrm.set_property("rotation-x",b) 
gltrnsfrm.set_property("rotation-y",c) 

#dynamic controller
cs = GstController.InterpolationControlSource()
cs.set_property('mode', GstController.InterpolationMode.LINEAR)
cb= Gstcontorller.DirectControlBinding.new(gltrnsfrm,"rotation-x",cs)
gltrnsfrm.add_control_binding(cb)

#modify the values
cs.set(0*Gst.SECOND,b)  #use updated values of b
cs.set(1*Gst.SECOND,b)