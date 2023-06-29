import bpy
import math
import random

for i in range(100):
    context = bpy.context

    bpy.ops.wm.read_factory_settings(use_empty=True)

    scene = bpy.context.scene
    scene.objects.keys()

    out_dir = "/home/jason/Desktop/STUDY/blender_front/blender/blender-2.93.1-linux-x64/fluid_render/res/"

    bpy.ops.mesh.primitive_plane_add(size=200.0, calc_uvs=True, enter_editmode=False, align='WORLD',
                                    location=(0.0, 0.0, -0.4))

    file_loc_0 = '/home/jason/Desktop/STUDY/blender_front/blender/blender-2.93.1-linux-x64/fluid_render/fluid'+str(i)+'.obj'
    imported_object_0 = bpy.ops.import_scene.obj(filepath=file_loc_0)
    ov=bpy.context.copy()
    ov['area']=[a for a in bpy.context.screen.areas if a.type=="VIEW_3D"][0]
    bpy.ops.transform.rotate(ov,value=(math.pi * 0.5), orient_axis='X')  # value = Angle

    for ob in context.scene.objects:
        #if ob.type == 'MESH':
        if ob.name == 'fluid'+str(i):
            # smoothing the surface
            n = ob.modifiers.get("My Smoothing") or ob.modifiers.new('My Smooth','SMOOTH')
            n.factor = 3

            # subdivide the surface
            m = ob.modifiers.get("My SubDiv") or ob.modifiers.new('My SubDiv', 'SUBSURF')
            m.levels = 2
            m.render_levels = 3
            m.quality = 5

            mat = bpy.data.materials.new(name="MaterialName") #set new material to variable
            mat.diffuse_color = (0.005, 0.199, 0.800, 1.000)
            mat.show_transparent_back = True #  renders trans
            ob.data.materials.append(mat)
            ob.active_material = mat
            ob.show_transparent = True         
            print("ob len"+str(len(ob.data.materials)))
            



    # attempt to add material
    #activeObject = bpy.context.active_object #Set active object to variable
    #mat = bpy.data.materials.new(name="MaterialName") #set new material to variable
    #activeObject.data.materials.append(mat) #add the material to the object
    #bpy.context.object.active_material.diffuse_color = (0.667, 0.985, 0.800, 1.000) #change color


    bpy.context.view_layer.update()


    bpy.ops.object.camera_add(enter_editmode=False, align='WORLD', location=(6.8713, -9.0453, 4.4753),
                        rotation=(1.317724, 0.012182398, 0.6161012), scale=(1.0, 1.0, 1.0))
    scene.camera = bpy.context.object
    scene.cycles.device = 'GPU'

    prefs = bpy.context.preferences
    cprefs = prefs.addons['cycles'].preferences

    # Attempt to set GPU device types if available
    for compute_device_type in ('CUDA', 'OPENCL', 'NONE'):
        try:
            cprefs.compute_device_type = compute_device_type
            break
        except TypeError:
            pass

    # Enable all CPU and GPU devices
    cprefs.get_devices()
    for device in cprefs.devices:
        device.use = True

    # create light datablock, set attributes
    light_data = bpy.data.lights.new(name="light_2.80", type='POINT')
    light_data.energy = 1800

    # create new object with our light datablock
    light_object = bpy.data.objects.new(name="light_2.80", object_data=light_data)

    # link light object
    bpy.context.collection.objects.link(light_object)

    # make it active
    bpy.context.view_layer.objects.active = light_object

    # change location
    light_object.location = (-2.3533, -0.3375, 4.2374)

    bpy.context.scene.render.engine = 'CYCLES'
    bpy.context.scene.cycles.device = 'GPU'
    #bpy.context.scene.render.resolution_percentage = 200
    bpy.context.scene.cycles.samples = 512
    bpy.context.scene.render.resolution_x = 3840
    bpy.context.scene.render.resolution_y = 2160
    bpy.context.scene.render.filepath = out_dir + "test"+str(i)+".png"
    # bpy.context.scene.render.image_settings.compression = 50
    bpy.context.scene.render.image_settings.color_mode = 'RGBA'
    bpy.context.scene.render.image_settings.file_format = 'PNG'
    bpy.ops.render.render(write_still=True)
