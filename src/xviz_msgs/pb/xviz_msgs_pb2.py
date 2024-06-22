# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: xviz_msgs.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0fxviz_msgs.proto\x12\txviz_msgs\"5\n\x06Header\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0f\n\x07\x66rameId\x18\x02 \x01(\t\x12\x0c\n\x04info\x18\x03 \x01(\t\" \n\x08Vector2f\x12\t\n\x01x\x18\x01 \x01(\x02\x12\t\n\x01y\x18\x02 \x01(\x02\"_\n\x06Pose2f\x12!\n\x06header\x18\x01 \x01(\x0b\x32\x11.xviz_msgs.Header\x12%\n\x08position\x18\x02 \x01(\x0b\x32\x13.xviz_msgs.Vector2f\x12\x0b\n\x03yaw\x18\x03 \x01(\x02\"V\n\x0bPose2fArray\x12!\n\x06header\x18\x01 \x01(\x0b\x32\x11.xviz_msgs.Header\x12$\n\tposeArray\x18\x02 \x03(\x0b\x32\x11.xviz_msgs.Pose2f\"c\n\tPolygon2f\x12!\n\x06header\x18\x01 \x01(\x0b\x32\x11.xviz_msgs.Header\x12#\n\x06points\x18\x02 \x03(\x0b\x32\x13.xviz_msgs.Vector2f\x12\x0e\n\x06\x66illed\x18\x03 \x01(\x08\"_\n\x0ePolygon2fArray\x12!\n\x06header\x18\x01 \x01(\x0b\x32\x11.xviz_msgs.Header\x12*\n\x0cpolygonArray\x18\x02 \x03(\x0b\x32\x14.xviz_msgs.Polygon2f\"b\n\x06Path2f\x12!\n\x06header\x18\x01 \x01(\x0b\x32\x11.xviz_msgs.Header\x12#\n\x06points\x18\x02 \x03(\x0b\x32\x13.xviz_msgs.Vector2f\x12\x10\n\x08isDashed\x18\x03 \x01(\x08\"V\n\x0bPath2fArray\x12!\n\x06header\x18\x01 \x01(\x0b\x32\x11.xviz_msgs.Header\x12$\n\tpathArray\x18\x02 \x03(\x0b\x32\x11.xviz_msgs.Path2f\"r\n\x08\x43ircle2f\x12!\n\x06header\x18\x01 \x01(\x0b\x32\x11.xviz_msgs.Header\x12#\n\x06\x63\x65nter\x18\x02 \x01(\x0b\x32\x13.xviz_msgs.Vector2f\x12\x0e\n\x06radius\x18\x03 \x01(\x02\x12\x0e\n\x06\x66illed\x18\x04 \x01(\x08\"\\\n\rCircle2fArray\x12!\n\x06header\x18\x01 \x01(\x0b\x32\x11.xviz_msgs.Header\x12(\n\x0b\x63ircleArray\x18\x02 \x03(\x0b\x32\x13.xviz_msgs.Circle2f\"V\n\x0cPointCloud2f\x12!\n\x06header\x18\x01 \x01(\x0b\x32\x11.xviz_msgs.Header\x12#\n\x06points\x18\x02 \x03(\x0b\x32\x13.xviz_msgs.Vector2f\"\xcb\x02\n\x08Marker2f\x12!\n\x06header\x18\x01 \x01(\x0b\x32\x11.xviz_msgs.Header\x12\x0c\n\x04type\x18\x02 \x01(\r\x12\x1f\n\x04path\x18\x03 \x01(\x0b\x32\x11.xviz_msgs.Path2f\x12%\n\x07polygon\x18\x04 \x01(\x0b\x32\x14.xviz_msgs.Polygon2f\x12#\n\x06\x63irlce\x18\x05 \x01(\x0b\x32\x13.xviz_msgs.Circle2f\x12\x1f\n\x04pose\x18\x06 \x01(\x0b\x32\x11.xviz_msgs.Pose2f\x12,\n\x0bpoint_cloud\x18\x07 \x01(\x0b\x32\x17.xviz_msgs.PointCloud2f\x12\x0c\n\x04text\x18\x08 \x01(\t\x12\x11\n\tcolorType\x18\t \x01(\r\x12\x0e\n\x06length\x18\n \x01(\x02\x12\x11\n\tthickness\x18\x0b \x01(\x02\x12\x0e\n\x06radius\x18\x0c \x01(\x02\"\\\n\rMarker2fArray\x12!\n\x06header\x18\x01 \x01(\x0b\x32\x11.xviz_msgs.Header\x12(\n\x0bmarkerArray\x18\x02 \x03(\x0b\x32\x13.xviz_msgs.Marker2f\"\x8f\x01\n\x0fTransform2fNode\x12!\n\x06header\x18\x01 \x01(\x0b\x32\x11.xviz_msgs.Header\x12\"\n\x05trans\x18\x02 \x01(\x0b\x32\x13.xviz_msgs.Vector2f\x12\r\n\x05\x61ngle\x18\x03 \x01(\x02\x12\x0f\n\x07\x66rameId\x18\x04 \x01(\t\x12\x15\n\rparentFrameId\x18\x05 \x01(\t\"q\n\tMapDouble\x12,\n\x04\x64\x61ta\x18\x01 \x03(\x0b\x32\x1e.xviz_msgs.MapDouble.DataEntry\x12\t\n\x01t\x18\x02 \x01(\x01\x1a+\n\tDataEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\x01:\x02\x38\x01\"f\n\tMapString\x12,\n\x04\x64\x61ta\x18\x01 \x03(\x0b\x32\x1e.xviz_msgs.MapString.DataEntry\x1a+\n\tDataEntry\x12\x0b\n\x03key\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\t:\x02\x38\x01\x62\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'xviz_msgs_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _MAPDOUBLE_DATAENTRY._options = None
  _MAPDOUBLE_DATAENTRY._serialized_options = b'8\001'
  _MAPSTRING_DATAENTRY._options = None
  _MAPSTRING_DATAENTRY._serialized_options = b'8\001'
  _HEADER._serialized_start=30
  _HEADER._serialized_end=83
  _VECTOR2F._serialized_start=85
  _VECTOR2F._serialized_end=117
  _POSE2F._serialized_start=119
  _POSE2F._serialized_end=214
  _POSE2FARRAY._serialized_start=216
  _POSE2FARRAY._serialized_end=302
  _POLYGON2F._serialized_start=304
  _POLYGON2F._serialized_end=403
  _POLYGON2FARRAY._serialized_start=405
  _POLYGON2FARRAY._serialized_end=500
  _PATH2F._serialized_start=502
  _PATH2F._serialized_end=600
  _PATH2FARRAY._serialized_start=602
  _PATH2FARRAY._serialized_end=688
  _CIRCLE2F._serialized_start=690
  _CIRCLE2F._serialized_end=804
  _CIRCLE2FARRAY._serialized_start=806
  _CIRCLE2FARRAY._serialized_end=898
  _POINTCLOUD2F._serialized_start=900
  _POINTCLOUD2F._serialized_end=986
  _MARKER2F._serialized_start=989
  _MARKER2F._serialized_end=1320
  _MARKER2FARRAY._serialized_start=1322
  _MARKER2FARRAY._serialized_end=1414
  _TRANSFORM2FNODE._serialized_start=1417
  _TRANSFORM2FNODE._serialized_end=1560
  _MAPDOUBLE._serialized_start=1562
  _MAPDOUBLE._serialized_end=1675
  _MAPDOUBLE_DATAENTRY._serialized_start=1632
  _MAPDOUBLE_DATAENTRY._serialized_end=1675
  _MAPSTRING._serialized_start=1677
  _MAPSTRING._serialized_end=1779
  _MAPSTRING_DATAENTRY._serialized_start=1736
  _MAPSTRING_DATAENTRY._serialized_end=1779
# @@protoc_insertion_point(module_scope)
